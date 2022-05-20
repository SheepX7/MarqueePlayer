#include <string>
#include <stdlib.h>
#include <jni.h>

extern "C" {
#include <libavcodec/avfft.h>
#include "libavcodec/packet.h"
#include "libavutil/frame.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfilter.h"
#include <libavformat/avformat.h>
#include "libavutil/time.h"
#include "libavutil/avstring.h"
}
#include "sdl/sdl_thread.h"
#include "sdl/sdl_mutex.h"
#include "sdl/marquee_sdl.h"
#include "sdl/sdl_audiospec.h"



#define FRAME_QUEUE_SIZE 16
#define SAMPLE_ARRAY_SIZE (8 * 65536)
#define SDL_AUDIO_MIN_BUFFER_SIZE 512
#define SDL_AUDIO_MAX_CALLBACKS_PER_SEC 30
using namespace uranus::sdl;

namespace uranus {
    namespace marquee {
        class MyAVPacketList {
            AVPacket pkt;
            struct MyAVPacketList *next;
            int serial;
        };

        class PacketQueue {
        public:
            MyAVPacketList *first_pkt, *last_pkt;
            int nb_packets;
            int size;
            int64_t duration;
            int abort_request;
            int serial;
            SDL_cond *cond;
            SDL_mutex *mutex;
        };

        class Frame {
        public:
            AVFrame *frame;
            AVSubtitle sub;
            int serial;
            double pts;           /* presentation timestamp for the frame */
            double duration;      /* estimated duration of the frame */
            int64_t pos;          /* byte position of the frame in the input file */
            int width;
            int height;
            int format;
            AVRational sar;
            int uploaded;
            int flip_v;
        };

        class FrameQueue {

        public:
            SDL_mutex *mutex;
            SDL_cond  *cond;
            Frame queue[FRAME_QUEUE_SIZE];
            int rindex;
            int windex;
            int size;
            int max_size;
            int keep_last;
            int rindex_shown;
            PacketQueue *pktq;
        };

        class Clock {
        public:
            double pts;           /* clock base */
            double pts_drift;     /* clock base minus time at which we updated the clock */
            double last_updated;
            double speed;
            int serial;           /* clock is based on a packet with this serial */
            int paused;
            int *queue_serial;    /* pointer to the current packet queue serial, used for obsolete clock detection */
        };

        class Decoder {
        public:
            AVPacket pkt;
            PacketQueue *queue;
            AVCodecContext *avctx;
            int pkt_serial;
            int finished;
            int packet_pending;
            SDL_cond *empty_queue_cond;
            int64_t start_pts;
            AVRational start_pts_tb;
            int64_t next_pts;
            AVRational next_pts_tb;
            SDL_Thread *decoder_tid;
        };

        enum {
            AV_SYNC_AUDIO_MASTER, /* default choice */
            AV_SYNC_VIDEO_MASTER,
            AV_SYNC_EXTERNAL_CLOCK, /* synchronize to an external clock */
        };

        class AudioParams {
        public:
            int freq;
            int channels;
            int64_t channel_layout;
            enum AVSampleFormat fmt;
            int frame_size;
            int bytes_per_sec;
        };

        class VideoState {
        public:
            SDL_Thread *read_tid;
            SDL_Thread *_read_tid;
            AVInputFormat *iformat;
            int abort_request;
            int force_refresh;
            int paused;
            int last_paused;
            int queue_attachments_req;
            int seek_req;
            int seek_flags;
            int64_t seek_pos;
            int64_t seek_rel;
            int read_pause_return;
            AVFormatContext *ic;
            int realtime;

            Clock audclk;
            Clock vidclk;
            Clock extclk;

            FrameQueue pictq;
            FrameQueue subpq;
            FrameQueue sampq;

            Decoder auddec;
            Decoder viddec;
            Decoder subdec;

            int audio_stream;

            int av_sync_type;

            double audio_clock;
            int audio_clock_serial;
            double audio_diff_cum; /* used for AV difference average computation */
            double audio_diff_avg_coef;
            double audio_diff_threshold;
            int audio_diff_avg_count;
            AVStream *audio_st;
            PacketQueue audioq;
            int audio_hw_buf_size;
            uint8_t *audio_buf;
            uint8_t *audio_buf1;
            unsigned int audio_buf_size; /* in bytes */
            unsigned int audio_buf1_size;
            int audio_buf_index; /* in bytes */
            int audio_write_buf_size;
            int audio_volume;
            int muted;
            struct SwrContext *swr_ctx;
            int frame_drops_early;
            int frame_drops_late;

            enum ShowMode {
                SHOW_MODE_NONE = -1, SHOW_MODE_VIDEO = 0, SHOW_MODE_WAVES, SHOW_MODE_RDFT, SHOW_MODE_NB
            } show_mode;
            int16_t sample_array[SAMPLE_ARRAY_SIZE];
            int sample_array_index;
            int last_i_start;
            RDFTContext *rdft;
            int rdft_bits;
            FFTSample *rdft_data;
            int xpos;
            double last_vis_time;
            SDL_Texture *vis_texture;
            SDL_Texture *sub_texture;
            SDL_Texture *vid_texture;

            int subtitle_stream;
            AVStream *subtitle_st;
            PacketQueue subtitleq;

            double frame_timer;
            double frame_last_returned_time;
            double frame_last_filter_delay;
            int video_stream;
            AVStream *video_st;
            PacketQueue videoq;
            double max_frame_duration;      // maximum duration of a frame - above this, we consider the jump a timestamp discontinuity
            struct SwsContext *img_convert_ctx;
            struct SwsContext *sub_convert_ctx;
            int eof;

            char *filename;
            int width, height, xleft, ytop;
            int step;

        #if CONFIG_AVFILTER
                    int vfilter_idx;
            AVFilterContext *in_video_filter;   // the first filter in the video chain
            AVFilterContext *out_video_filter;  // the last filter in the video chain
            AVFilterContext *in_audio_filter;   // the first filter in the audio chain
            AVFilterContext *out_audio_filter;  // the last filter in the audio chain
            AVFilterGraph *agraph;              // audio filter graph
        #endif
            int last_video_stream, last_audio_stream, last_subtitle_stream;

            SDL_cond *continue_read_thread;
            AudioParams audio_src;
            AudioParams audio_tgt;
        };

        class FFPlayer {
            public:
                const AVClass *avClass;
                VideoState *is;
                AVDictionary *format_opts;
                AVDictionary *codec_opts;
                AVDictionary *sws_dict;
                AVDictionary *player_opts;
                AVDictionary *swr_opts;
                AVDictionary *swr_preset_opts;

                int startup_volume = 100;
                int av_sync_type = AV_SYNC_AUDIO_MASTER;

            public:
                VideoState* stream_open(const char* filename, AVInputFormat *iformat);

#ifdef FFMEG
            void set_default_window_size(int width, int height, AVRational sar);
#endif


            int genpts = 0;
            int find_stream_info = 1;
            int seek_by_bytes;
            char* window_title;
            int64_t start_time = AV_NOPTS_VALUE;
            int show_status = -1;
            int audio_disable;
            int video_disable;
            int subtitle_disable;
            enum VideoState::ShowMode show_mode = VideoState::SHOW_MODE_NONE;
            int default_width  = 640;
            int default_height = 480;
            int screen_width  = 0;
            int screen_height = 0;

            const char* wanted_stream_spec[AVMEDIA_TYPE_NB] = {0};

            bool fast;
            int audio_dev;
        };

        class MarqueePlayer {
            public:
                FFPlayer  *ffPlayer;

            void open(const char *pJstring);
        };
    }
}