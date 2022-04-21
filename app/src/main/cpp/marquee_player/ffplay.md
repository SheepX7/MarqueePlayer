## stream_component_open
1. 通过 avcodec_alloc_context2 分配 AVCodecContext
2. 填充 AVCodecContext 数据，avcodec_parameters_to_context
3. 根据 codec_id 找到 AVCodec，avcodec_find_decoder
4. 根据 codec_name 找到 AVCodec, avcodec_find_decoder_by_name (可选)
5. 设置用户选项，重新打开 AVCodecContext
6. 根据 codec_type 开启线程进行解码, AVMEDIA_TYPE_AUDIO, AVMEDIA_TYPE_VIDEO, AVMEDIA_TYPE_SUBLITE。
7. AVMEDIA_TYPE_AUDIO : audio_open->decoder_init->decoder_start(&is->auddec, audio_thread, "audio_decoder", is)
8. AVMEDIA_TYPE_VIDEO : decoder_init->decoder_start(&is->viddec, video_thread, "video_decoder", is)
9. AVMEDIA_TYPE_SUBLITE : decoder_init->decoder_start(&is->subdec, subtitle_thread, "subtitle_decoder", is)

## audio_open
1. 

## decoder_init