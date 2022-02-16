//
// Created by Mico on 2022/2/16.
//
#include "libavfilter/avfilter.h"

void init();

namespace uranus {
    namespace marquee {
        class VideoState {

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

            public:
                void ffp_global_init();
        };

        class MarqueePlayer {
            public:
                FFPlayer  *ffPlayer;
        };
    }
}