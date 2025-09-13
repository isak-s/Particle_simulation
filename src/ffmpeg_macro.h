#ifndef FFMPEG_MACRO
#define FFMPEG_MACRO

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define FFMPEG_CMD \
    "ffmpeg -y -f rawvideo " \
    "-pixel_format rgb24 " \
    "-video_size " STR(WIDTH) "x" STR(HEIGHT) " " \
    "-framerate " STR(FRAMERATE) " " \
    "-i - -c:v libx264 " \
    "-preset veryfast " \
    "-pix_fmt yuv420p " \
    OUTPUT_FILE

#endif