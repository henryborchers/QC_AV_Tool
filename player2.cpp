//
// Created by Henry on 7/8/2015.
//

#include "player2.h"
extern "C"{
#include <libavutil/avstring.h>
#include <libavutil/opt.h>
#include <libswresample/swresample.h>
#include <libavutil/version.h>

}

// Constants
const Version _playerVersion = {2, 0, 0};
const Version _avcodecVersion = {LIBAVCODEC_VERSION_MAJOR,
                                 LIBAVCODEC_VERSION_MINOR,
                                 LIBAVCODEC_VERSION_MICRO};

const Version _avformatVersion = {LIBAVFORMAT_VERSION_MAJOR,
                                  LIBAVFORMAT_VERSION_MINOR,
                                  LIBAVFORMAT_VERSION_MICRO};

const Version _swscaleVersion = {LIBSWSCALE_VERSION_MAJOR,
                                 LIBSWSCALE_VERSION_MINOR,
                                 LIBSWSCALE_VERSION_MICRO};
static const int SDL_AUDIO_BUFFER_SIZE = 1024;
static const int MAX_AUDIO_FRAME_SIZE = 192000;
static const int MAX_AUDIOQ_SIZE = 5 * 16 * 1024;
static const int MAX_VIDEOQ_SIZE = 5 * 256 * 1024;

#define FF_ALLOC_EVENT (SDL_USEREVENT)
#define FF_REFRESH_EVENT (SDL_USEREVENT + 1)
#define FF_QUIT_EVENT (SDL_USEREVENT + 2)

const Version &playerVersion() {
    return _playerVersion;
}

const Version &SDLVersion() {
    SDL_version compiled;
    SDL_GetVersion(&compiled);

    static Version mySDL;
    mySDL.major = compiled.major;
    mySDL.minor = compiled.minor;
    mySDL.micro = compiled.patch;
    return mySDL;
}

// global variable
VideoState      *global_video_state;
SDL_mutex       *window_mutex;
int             quit = 0;
PacketQueue     audioq;
SDL_AudioDeviceID   dev;
SwrContext      *swr;

const Version &avcodecVersion() {
    return _avcodecVersion;
//    return nullptr;
}
const Version &avformatVersion() {
    return _avformatVersion;
}

const Version &swscaleVersion() {
    return _swscaleVersion;
}



void packet_queue_init(PacketQueue *q) {
    memset(q, 0, sizeof(PacketQueue));
    q->mutex = SDL_CreateMutex();
    q->cond = SDL_CreateCond();
}

int packet_queue_put(PacketQueue *q, AVPacket *pkt) {
    AVPacketList *pkt1 = nullptr;
    if(av_dup_packet(pkt) < 0) {
        return -1;
    }
    pkt1 = (AVPacketList*)av_malloc(sizeof(AVPacketList));
    if(!pkt1)
        return  -1;
    pkt1->pkt = *pkt;
    pkt1->next = nullptr;
    SDL_LockMutex(q->mutex);
    if (!q->last_pkt)
        q->first_pkt = pkt1;
    else
        q->last_pkt->next = pkt1;
    q->last_pkt = pkt1;
    q->nb_packets++;
    q->size += pkt1->pkt.size;
    SDL_CondSignal(q->cond);
    SDL_UnlockMutex(q->mutex);
    return 0;
}

static int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block) {
    // Should be good!
    AVPacketList *pkt1;
    int ret;

    SDL_LockMutex(q->mutex);
    for(;;) {

        if (global_video_state->quit) {
            ret = -1;
            break;
        }

        pkt1 = q->first_pkt;
        if (pkt1) {
            q->first_pkt = pkt1->next;
            if (!q->first_pkt)
                q->last_pkt = NULL;
            q->nb_packets --;
            q->size -= pkt1->pkt.size;
            *pkt = pkt1->pkt;
            av_free(pkt1);
            ret = 1;
            break;
        } else if (!block) {
            ret = 0;
            break;
        } else {

            SDL_CondWait(q->cond, q->mutex);
        }
    }
    SDL_UnlockMutex(q->mutex);
    return ret;
}

bool ffmpeg_player2(const char fileName[]) {
//    printf("ffmpeg_threads with %s\n",fileName);
    SDL_Event   event;
    VideoState  *is = (VideoState*)av_mallocz(sizeof(VideoState));
    AVFormatContext *inputFmtCtx = nullptr;
    int videoHeight = -1;
    int videoWidth = -1;

    struct SDL_Window  *pScreen;
    struct SDL_Renderer *pRenderer;
    av_register_all();

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        fprintf(stderr, "Couldn't initalize SDL %s.\n", SDL_GetError());
        return false;
    }

    // get the video resolution
    if(avformat_open_input(&inputFmtCtx, fileName, nullptr, nullptr)!=0){
        return false;
    }
    if(avformat_find_stream_info(inputFmtCtx, nullptr)<0){
        return false;
    }

    for(int i = 0; i<inputFmtCtx->nb_streams; i++){
        if(inputFmtCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
            videoHeight = inputFmtCtx->streams[i]->codec->coded_height;
            videoWidth = inputFmtCtx->streams[i]->codec->coded_width;
            break;
        }
    }

    if(videoHeight <= 0 || videoWidth <= 0){
        return false;
    }
    avformat_close_input(&inputFmtCtx);


    pScreen = SDL_CreateWindow("FFMPEG player 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, videoWidth, videoHeight, SDL_WINDOW_SHOWN);
    if(!pScreen){
        fprintf(stderr, "SDL: Couldn't set video mode. exiting\n");
        exit(1);
    }

    pRenderer = SDL_CreateRenderer(pScreen, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STATIC, 720, 480);

    av_strlcpy(is->filename, fileName, sizeof(is->filename));
    is->pictq_mutex = SDL_CreateMutex();
    is->pictq_cond = SDL_CreateCond();



    schedule_refresh(is, 40);

    is->parse_tid = SDL_CreateThread(decode_thread,"parse_thread", is);
    if(!is->parse_tid){
        av_free(is);
        return false;
    }



    for(;;) {

        SDL_WaitEvent(&event);
        switch(event.type) {
            case FF_QUIT_EVENT:
            case SDL_QUIT:
//                puts("Quiting");
                is->quit = 1;
                SDL_CondSignal(is->audioq.cond);
                SDL_CondSignal(is->videoq.cond);

                SDL_Quit();
                return true;
                break;
            case FF_ALLOC_EVENT:
                alloc_picture(event.user.data1,pRenderer);
                break;
            case FF_REFRESH_EVENT:
                video_refresh_timer(event.user.data1, pRenderer, texture);
                break;
            default:
                break;
        }
    }
    SDL_DestroyTexture(texture);

    return true;

}

static void schedule_refresh(VideoState *is, int delay) {
    SDL_AddTimer(delay, sdl_refresh_timer_cb, is);
}

int decode_thread(void *arg) {

//    puts("Decoder_thread");
    VideoState      *is = (VideoState*)arg;
    AVFormatContext *pFormatCtx = nullptr;
    AVPacket        pkt1;
    AVPacket        *packet = &pkt1;



    int video_index = -1;
    int audio_index = -1;
//    int i;

    AVDictionary *io_dict = nullptr;
    AVIOInterruptCB callback;

    is->videoStream = -1;
    is->audioStream = -1;



    global_video_state = is;
    callback.callback = decode_interrupt_cb;
    callback.opaque = is;
    if(avio_open2(&is->io_context, is->filename, 0, &callback, &io_dict)) {
        fprintf(stderr, "unable to open I/O for %s\n",is->filename);
        return -1;
    }

    if(avformat_open_input(&pFormatCtx, is->filename, nullptr, nullptr) !=0){
        return -1;
    }

    is->pFormatCtx = pFormatCtx;

    if(avformat_find_stream_info(pFormatCtx, nullptr) <0)
        return -1;

    av_dump_format(pFormatCtx, 0, is->filename, 0);
    for(int i = 0; i<pFormatCtx->nb_streams; i++){

        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO && video_index < 0) {
            video_index = i;
        }
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO && audio_index < 0) {
            audio_index = i;
        }
    }

    if(audio_index >= 0) {
        stream_component_open(is, audio_index);
    }
    if(video_index >= 0) {
        stream_component_open(is, video_index);
    }

    if(is->videoStream < 0 || is->videoStream < 0) {
        fprintf(stderr, "%s: could not open codecs\n", is->filename);
        goto fail;
    }
// Main Decode loop
    for(;;) {
        if (is->quit) {
            break;
        }
        if (is->audioq.size > MAX_AUDIOQ_SIZE || is->videoq.size > MAX_VIDEOQ_SIZE) {
            SDL_Delay(10);
            continue;
        }

        if (av_read_frame(is->pFormatCtx, packet) < 0) {

            if (is->pFormatCtx->pb->error == 0) {
                SDL_Delay(100);
                continue;
            } else {
                break;
            }
        }

        if(packet->stream_index == is->videoStream) {
            packet_queue_put(&is->videoq, packet);
        } else if(packet->stream_index == is->audioStream){
            packet_queue_put(&is->audioq, packet);
        } else {
            av_free_packet(packet);
        }
    }
    while(!is->quit) {
        SDL_Delay(100);
    }
    fail:
    if(1){
        SDL_Event event;
        event.type = FF_QUIT_EVENT;
        event.user.data1 = is;
        SDL_PushEvent(&event);
    }
    return 0;
}

int stream_component_open(VideoState *is, int stream_index) {

    AVFormatContext     *pFormatCtx = is->pFormatCtx;
    AVCodecContext      *codecCtx = nullptr;
    AVCodec             *codec = nullptr;
    AVDictionary        *optionsDict = nullptr;
    SDL_AudioSpec       wanted_spec;
    SDL_AudioSpec       spec;

//    if problems check here
    if(stream_index < 0 || stream_index >= pFormatCtx->nb_streams){
        return -1;
    }
    codecCtx = pFormatCtx->streams[stream_index]->codec;


    if(codecCtx->codec_type == AVMEDIA_TYPE_AUDIO){
        SDL_zero(wanted_spec);

        if(codecCtx->sample_fmt == AV_SAMPLE_FMT_S16P) {
//            puts("Special case");
            codecCtx->request_sample_fmt=AV_SAMPLE_FMT_S16;
        }


//        SDL_zero(spec);
        wanted_spec.freq = codecCtx->sample_rate;
        wanted_spec.format = AUDIO_S16SYS;
        wanted_spec.channels = (Uint8)codecCtx->channels;
        wanted_spec.silence = 0;
        wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
        wanted_spec.callback = audio_callback2;
        wanted_spec.userdata = is;

        if(SDL_OpenAudio(&wanted_spec, &spec) < 0) {
            fprintf(stderr, "SDL_OpenAudio error: %s\n", SDL_GetError());
            return -1;
        }
    }

    codec = avcodec_find_decoder(codecCtx->codec_id);
    if(!codec || (avcodec_open2(codecCtx, codec, &optionsDict) < 0)){
        fprintf(stderr, "Unsupported Codec!\n");
        return -1;
    }
    if(codecCtx->sample_fmt == AV_SAMPLE_FMT_FLTP) {
        puts("Special case 2");
        //FIXME
//        swr = swr_alloc();
        av_opt_set_int(swr, "in_channel_layout", codecCtx->channel_layout, 0);
        av_opt_set_int(swr, "out_channel_layout", codecCtx->channel_layout, 0);
//        av_opt_set_int(swr, "out_channel_layout", codecCtx->channel_layout, 0);

//            codecCtx->request_sample_fmt=AV_SAMPLE_FMT_FLT;
    }


    switch(codecCtx->codec_type){
        case AVMEDIA_TYPE_AUDIO:
            is->audioStream = stream_index;
            is->audio_st = pFormatCtx->streams[stream_index];
            is->audio_buf_size = 0;
            is->audio_buf_index = 0;
            memset(&is->audio_pkt, 0, sizeof(is->audio_pkt));
            packet_queue_init(&is->audioq);
            SDL_PauseAudio(0);
            break;
        case AVMEDIA_TYPE_VIDEO:
            is->videoStream = stream_index;
            is->video_st = pFormatCtx->streams[stream_index];

            packet_queue_init(&is->videoq);
            is->video_tid = SDL_CreateThread(video_thread, "video_thread", is);


            is->sws_ctx = sws_getContext(is->video_st->codec->width,
                                         is->video_st->codec->height,
                                         is->video_st->codec->pix_fmt,
                                         is->video_st->codec->width,
                                         is->video_st->codec->height,
                                         PIX_FMT_YUV420P,
                                         SWS_BILINEAR,
                                         nullptr,
                                         nullptr,
                                         nullptr
            );

            break;
        default:
            break;
    }
    return 0;
}

int video_thread(void *arg) {
    VideoState *is = (VideoState *)arg;
    AVPacket pkt1, *packet = &pkt1;
    int frameFinished;
    AVFrame *pFrame;
//    puts("Video Thread in");
    pFrame = av_frame_alloc();

    for(;;) {
        if(packet_queue_get(&is->videoq, packet, 1) < 0) {
            break;
        }

        avcodec_decode_video2(is->video_st->codec, pFrame, &frameFinished, packet);
//        printf("frame finished %d\n",frameFinished);
        if(frameFinished) {

            if(queue_picture(is, pFrame) < 0){
                break;
            }
        }
        av_free_packet(packet);
//        puts("Video Thread packet free");
    }
    av_free(&pFrame);
    return 0;
}

int queue_picture(VideoState *is, AVFrame *pFrame) {
//    puts("queue_picture in");
    VideoPicture *vp;
//    int dst_pix_fmt;
//    AVPicture pict;

    SDL_LockMutex(is->pictq_mutex);
    while(is->pictq_size >= VIDEO_PICTURE_QUEUE_SIZE && !is->quit) {
        SDL_CondWait(is->pictq_cond, is->pictq_mutex);
    }

    SDL_UnlockMutex(is->pictq_mutex);
    if(is->quit){
        return -1;
    }

    vp = &is->pictq[is->pictq_windex];

    if(!vp->rawdata ||
       vp->width != is->video_st->codec->width ||
       vp->height != is->video_st->codec->height) {
        SDL_Event event;

//        printf("is->quit: %d\n",is->quit);

        vp->allocated = 0;
        event.type = FF_ALLOC_EVENT;
        event.user.data1 = is;
        SDL_PushEvent(&event);

        SDL_LockMutex(is->pictq_mutex);
        while (!vp->allocated && !is->quit){
            SDL_CondWait(is->pictq_cond, is->pictq_mutex);
        }
        SDL_UnlockMutex(is->pictq_mutex);
//        alloc_picture(is, nullptr);
        if(is->quit) {
            return -1;
        }
    }


    if(vp->rawdata) {

        sws_scale(
                is->sws_ctx,
                (uint8_t const * const *)pFrame->data,
                pFrame->linesize,
                0,
                is->video_st->codec->height,
                vp->rawdata->data,
                vp->rawdata->linesize
        );
//        dst_pix_fmt = PIX_FMT_YUV420P;
//        puts("vp->bmp");
////        SDL_LockTexture(vp->bmp, nullptr, nullptr, nullptr);
//
//        SDL_UpdateYUVTexture(vp->bmp, NULL,
//                             pFrame->data[0], pFrame->linesize[0],
//                             pFrame->data[1], pFrame->linesize[1],
//                             pFrame->data[2], pFrame->linesize[2]);
////        SDL_RenderCopy(renderer2, vp->bmp, NULL, NULL);
////        SDL_RenderPresent(renderer2);
//
        if(++is->pictq_windex == VIDEO_PICTURE_QUEUE_SIZE) {
            is->pictq_windex = 0;
        }
        SDL_LockMutex(is->pictq_mutex);
        is->pictq_size++;
        SDL_UnlockMutex(is->pictq_mutex);
    }
    return 0;
}

void alloc_picture(void *userdata, SDL_Renderer *renderer) {
    VideoState *is = (VideoState *)userdata;
    VideoPicture *vp;

    vp = &is->pictq[is->pictq_windex];
    if(vp->rawdata) {
//        SDL_DestroyTexture(vp->bmp);
        av_free(vp->rawdata);

    }
//    SDL_LockMutex(window_mutex);
//    window = SDL_CreateWindow("FFMPEG test 4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, is->video_st->codec->width, is->video_st->codec->height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
//
//    if(!window){
//        fprintf(stderr, "SDL: Couldn't open a window.\n");
//        exit(-1);
//    }
//    renderer2 = SDL_CreateRenderer(window, -1, 0);
//    vp->bmp = SDL_CreateTexture(renderer2, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STATIC, is->video_st->codec->width, is->video_st->codec->height);
//    SDL_UnlockMutex(window_mutex);

    vp->width = is->video_st->codec->width;
    vp->height = is->video_st->codec->height;
    AVCodecContext *pCodecCtx = nullptr;
    pCodecCtx = is->video_st->codec;

//    AVFrame *pFrameYUV = avcodec_alloc_frame();
    AVFrame *pFrameYUV = av_frame_alloc();
    if(pFrameYUV == nullptr) {
        return;
    }
    int numBytes = avpicture_get_size(PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes* sizeof(uint8_t));
    avpicture_fill((AVPicture*)pFrameYUV, buffer, PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);
    vp->rawdata = pFrameYUV;
    SDL_LockMutex(is->pictq_mutex);
    vp->allocated = 1;
    SDL_CondSignal(is->pictq_cond);
    SDL_UnlockMutex(is->pictq_mutex);

}

void video_display(VideoState *is, SDL_Renderer *renderer, SDL_Texture *texture) {

    SDL_Rect rect;
    VideoPicture *vp;
    float aspect_ratio;
//    int wo;
//    int w;
//    int ho;
//    int h;
//    int x = 0;
//    int y = 0;

//    int i;

    vp = &is->pictq[is->pictq_rindex];
    if(vp->rawdata) {
        if(is->video_st->codec->sample_aspect_ratio.num == 0) {
            aspect_ratio = 0;
        } else {
            aspect_ratio = av_q2d(is->video_st->codec->sample_aspect_ratio) * is->video_st->codec->width / is->video_st->codec->height;
        }
        if(aspect_ratio <= 0.0) {
            aspect_ratio = (float)is->video_st->codec->width / (float)is->video_st->codec->width;
        }

//        SDL_GetWindowSize(window, &wo, &ho);
//        w = wo;
//        h = ho;
////        FIXME: fix aspect ratio of the screen
//
//        w = ((int)rint(h*aspect_ratio)) & -3;
//        if(w > wo) {
//            w = wo;
//            h = ((int)rint(w / aspect_ratio)) & -3;
//        }
//
//        x = (wo - w) / 2;
//        y = (ho - h) /2;


        rect.x = 0;
        rect.y = 0;
        rect.w = vp->width;
        rect.h = vp->height;

//        SDL_UpdateTexture(texture, &rect, vp->rawdata->data[0], vp->rawdata->linesize[0]);
        SDL_UpdateYUVTexture(texture, nullptr,
                             vp->rawdata->data[0], vp->rawdata->linesize[0],
                             vp->rawdata->data[1], vp->rawdata->linesize[1],
                             vp->rawdata->data[2], vp->rawdata->linesize[2]);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &rect, &rect);
//        SDL_RenderCopy(renderer2, vp->bmp, nullptr, &rect);
        SDL_RenderPresent(renderer);
        // DISPLAY the vp->bmp to the rect
        SDL_UnlockMutex(window_mutex);
    }

}

static Uint32 sdl_refresh_timer_cb(Uint32 interval, void *opaque) {
    SDL_Event event;
    event.type = FF_REFRESH_EVENT;
    event.user.data1 = opaque;
    SDL_PushEvent(&event);
    return 0;
}

void video_refresh_timer(void *userdata, SDL_Renderer *renderer, SDL_Texture *texture) {
    VideoState *is = (VideoState*)userdata;
//    VideoPicture *vp;

    if(is->video_st) {
        if(is->pictq_size == 0) {
            schedule_refresh(is, 1);
        } else {
//            vp = &is->pictq[is->pictq_rindex];
            schedule_refresh(is, 30);

            video_display(is, renderer, texture);

            if(++is->pictq_rindex == VIDEO_PICTURE_QUEUE_SIZE) {
                is->pictq_rindex = 0;
            }

            SDL_LockMutex(is->pictq_mutex);
            is->pictq_size --;
            SDL_CondSignal(is->pictq_cond);
            SDL_UnlockMutex(is->pictq_mutex);
        }
    } else {
        schedule_refresh(is, 100);
    }
}

void audio_callback2(void *userdata, Uint8 *stream, int len) {
    VideoState *is = (VideoState *) userdata;
    int len1;
    int audio_size;

    while(len > 0) {
        if(is->audio_buf_index >= is->audio_buf_size){
            audio_size = audio_decode_frame1(is);
            if (audio_size < 0) {
                is->audio_buf_size = 1024;
                memset(is->audio_buf, 0, is->audio_buf_size);
            } else {
                is->audio_buf_size = audio_size;
            }
            is->audio_buf_index = 0;
        }
        len1 = is->audio_buf_size - is->audio_buf_index;

        if(len1 > len){
            len1 = len;
        }
        memcpy(stream, (uint8_t*)is->audio_buf + is->audio_buf_index, len1);
        len -= len1;
        stream += len1;
        is->audio_buf_index += len1;
    }


}

int audio_decode_frame1(VideoState *is) {
    int len1;
    int data_size = 0;
    AVPacket *pkt = &is->audio_pkt;

    for(;;){
        while(is->audio_pkt_size > 0){
            int got_frame = 0;


            len1 = avcodec_decode_audio4(is->audio_st->codec, &is->audio_frame, &got_frame, pkt);
            if(len1<0) {
                is->audio_pkt_size = 0;
                break;
            }
            data_size = 0;
            if(got_frame){
                data_size = av_samples_get_buffer_size(NULL,
                                                       is->audio_st->codec->channels,
                                                       is->audio_frame.nb_samples,
                                                       is->audio_st->codec->sample_fmt,
                                                       1);
//                printf("Buffer size: %d\n"
//                               "timestamp: %d\n",data_size, is->audio_frame.best_effort_timestamp);
                memcpy(is->audio_buf, is->audio_frame.data[0], data_size);
            }
            is->audio_pkt_data += len1;
            is->audio_pkt_size -= len1;
            if(data_size <= 0){
                continue;
            }
            return data_size;
        }
        if(pkt->data){
            av_free_packet(pkt);
        }
        if(is->quit) {
            return -1;
        }
        if(packet_queue_get(&is->audioq, pkt, 1) < 0) {
            return -1;
        }
        is->audio_pkt_data = pkt->data;
        is->audio_pkt_size = pkt->size;
//        av_free_packet(pkt);
    }
}

int decode_interrupt_cb(void *opaque) {
    return (global_video_state && global_video_state->quit);
}
