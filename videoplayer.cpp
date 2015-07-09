//
// Created by Henry Borchers on 4/25/2015.
//

#include "videoplayer.h"
#include <cstdio>
#include <SDL.h>
extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

int videoPlayer(const char filename[]) {
    AVFormatContext     *pFormatCtx = nullptr;
    AVCodecContext      *pCodecCtxOrig = nullptr;
    AVCodecContext      *pCodecCtx = nullptr;
    AVCodec             *pCodec = nullptr;
    AVFrame             *pFrame = nullptr;
    AVPacket            packet;



    struct SwsContext   *sws_ctx = nullptr;

    SDL_Surface         *screen = nullptr;
    SDL_Window          *window = nullptr;
    SDL_Renderer        *renderer = nullptr;
    SDL_Texture         *bmp;
    SDL_Event           e;

    int                 videoStream = -1;

    printf("Working with \"%s\".\n",filename);

    av_register_all();  // initialize FFMPEG

    //open the file as a format Context
    if(avformat_open_input(&pFormatCtx, filename, nullptr, nullptr) != 0) {
        fprintf(stderr, "Couldn't open file\n");
        return -2;
    }

    // Load the stream info
    if(avformat_find_stream_info(pFormatCtx, nullptr) <0) {
        fprintf(stderr, "Couldn't find any stream\n");
        return -2;
    };

    // find the video stream
    for(int i=0; i < pFormatCtx->nb_streams; i++){
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
            videoStream = i;
            break;
        }
    }
    if(videoStream==-1){
        fprintf(stderr, "Couldn't find a video stream.\n");
        return -2;
    }

    // load the original codec context of the video stream
    pCodecCtxOrig=pFormatCtx->streams[videoStream]->codec;

    // find the codec for the codec context
    pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);

    //copy the codec context
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0){
        fprintf(stderr, "Failed to copy codec context\n");
        return -2;
    }

    //open the codec
    if(avcodec_open2(pCodecCtx, pCodec, NULL) <0){
        fprintf(stderr, "Couldn't open the codec");
        return -2;
    }
//    printf("%s\n",pCodec->name);

    //////////////////////////////
    // SDL setup                //
    //////////////////////////////

    // initialize SDL2
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        fprintf(stderr, "SDL not working. SDL_Error: %s", SDL_GetError());
        return -2;
    };

    // Create SDL2 window
    window = SDL_CreateWindow("Henry's Crazy Video Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pCodecCtx->width,pCodecCtx->height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    // Create SDL Renderer
    renderer = SDL_CreateRenderer(window, -1,0);
    if(renderer == nullptr){
        fprintf(stderr, "Error loading Render\n");
        return -2;
    }

    // Create SDL Texture
    bmp = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STATIC, pCodecCtx->width, pCodecCtx->height);
    if(bmp== nullptr){
        fprintf(stderr, "Error creating Texture");
        return -2;
    }

    // Allocate a frame
    pFrame = av_frame_alloc();
    bool quit = false;
    int i = 0;
    int t = 23;

    // Read through all the frames and grab a packet of data
    while(av_read_frame(pFormatCtx, &packet)>=0 and !quit){
        // check if there is a new pollevent
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        if(t>0) t--;
                        break;

                    case SDLK_DOWN:
                        t++;
                        break;
                    default:
                        break;
                }
                printf("t:%d\n",t);
            }
        }

        // check if the packet is video
        if(packet.stream_index==videoStream){
            int frameFinished;

            //decode the packet into a frame
            avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
            if(frameFinished){
                // load the frame onto the texture
                SDL_UpdateYUVTexture(bmp, NULL,

//                                     &x, pFrame->linesize[0],
                                     pFrame->data[0], pFrame->linesize[0],
                                     pFrame->data[1], pFrame->linesize[1],
                                     pFrame->data[2], pFrame->linesize[2]);
            }
//            printf("%s\n", pFrame->data[0]);
            SDL_RenderCopy(renderer, bmp, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
        i++;
        SDL_Delay(t);
    }
    // Clean up
    av_free_packet((&packet));
//    SD:
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
    SDL_DestroyTexture(bmp);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
