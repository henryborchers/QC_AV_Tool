//
// Created by Henry on 7/8/2015.
//

#ifndef FFMPEG_MESSING_AROUND_PLAYER2_H
#define FFMPEG_MESSING_AROUND_PLAYER2_H
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <SDL.h>
#include <SDL_thread.h>

};

const int AVCODEC_MAX_AUDIO_FRAME_SIZE = 192000;
const int VIDEO_PICTURE_QUEUE_SIZE = 1;

typedef struct Version{
    int major;
    int minor;
    int micro;
}Version;

typedef struct PacketQueue {
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;

typedef struct VideoPicture {
    AVFrame *rawdata;
    int         width;
    int         height;
    int         allocated;
} VideoPicture;

typedef struct VideoState {
    AVFormatContext     *pFormatCtx;
    int                 videoStream;
    int                 audioStream;
    AVStream            *audio_st;
    PacketQueue         audioq;
    uint8_t             audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
    unsigned int        audio_buf_size;
    unsigned int        audio_buf_index;
    AVFrame             audio_frame;
    AVPacket            audio_pkt;
    uint8_t             *audio_pkt_data;
    int                 audio_pkt_size;
    AVStream            *video_st;
    PacketQueue         videoq;

    VideoPicture        pictq[VIDEO_PICTURE_QUEUE_SIZE];
    int                 pictq_size;
    int                 pictq_rindex;
    int                 pictq_windex;
    SDL_mutex           *pictq_mutex;
    SDL_cond            *pictq_cond;

    SDL_Thread          *parse_tid;
    SDL_Thread          *video_tid;
    char                filename[1024];
    int                 quit;
    AVIOContext         *io_context;
    struct SwsContext    *sws_ctx;
} VideoState;


const       Version &playerVersion();
const       Version &SDLVersion();
const       Version &avcodecVersion();
const       Version &avformatVersion();
const       Version &swscaleVersion();
bool        ffmpeg_player2(const char fileName[]);
void        packet_queue_init(PacketQueue *q);
int         packet_queue_put(PacketQueue *q, AVPacket *pkt);
static int  packet_queue_get(PacketQueue *q, AVPacket *pkt, int block);
static      Uint32 sdl_refresh_timer_cb(Uint32 interval, void *opaque);

static void schedule_refresh(VideoState *is, int delay);
void        video_display(VideoState *is, SDL_Renderer *renderer, SDL_Texture *texture);
void        video_refresh_timer(void *userdata, SDL_Renderer *renderer, SDL_Texture *texture);
void        alloc_picture(void *userdata, SDL_Renderer *renderer);
int         queue_picture(VideoState *is, AVFrame *pFrame);
int         video_thread(void *arg);
int         stream_component_open(VideoState *is, int stream_index);
int         decode_thread(void *arg);
void        audio_callback2(void *userdata, Uint8 *stream, int len);
int         audio_decode_frame1(VideoState *is);
int         decode_interrupt_cb(void *opaque);


#endif //FFMPEG_MESSING_AROUND_PLAYER2_H
