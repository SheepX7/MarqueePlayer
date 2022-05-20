# For more information about using CMake with Android Studio, read the
# documentation: https://d.sondroid.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("marqueeplayer")
include_directories(.)
include_directories(include/ffmpeg)
include_directories(marquee_player/system)
include_directories(marquee_player/sdl)
aux_source_directory(marquee_player PLAYER)
aux_source_directory(marquee_player/system SYSTEM)
aux_source_directory(marquee_player/sdl PLAYER_SDL)
aux_source_directory(socket PLAYER_SOCKET)

add_library( # Sets the name of the library.
        native-lib
        SHARED
        native-lib.cpp
        marquee_jni.cpp

        ${PLAYER}
        ${PLAYER_SDL}
        ${PLAYER_SOCKET}
        ${SYSTEM}
        )

set(LIBRARY_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../../../libs/${ANDROID_ABI})

message("abi:  ${ANDROID_ABI}")
message("依赖库存储位置：${LIBRARY_SOURCE_DIR}")

add_library(avcodec SHARED IMPORTED)
set_target_properties(
        avcodec
        PROPERTIES IMPORTED_LOCATION
        ${LIBRARY_SOURCE_DIR}/ffmpeg/libavcodec.so
)

add_library(avutil SHARED IMPORTED)
set_target_properties(
        avutil
        PROPERTIES IMPORTED_LOCATION
        ${LIBRARY_SOURCE_DIR}/ffmpeg/libavutil.so
)

add_library(avfilter SHARED IMPORTED)
set_target_properties(
        avfilter
        PROPERTIES IMPORTED_LOCATION
        ${LIBRARY_SOURCE_DIR}/ffmpeg/libavfilter.so
)

add_library(avformat SHARED IMPORTED)
set_target_properties(
        avformat
        PROPERTIES IMPORTED_LOCATION
        ${LIBRARY_SOURCE_DIR}/ffmpeg/libavformat.so
)

add_library(postproc SHARED IMPORTED)
set_target_properties(
        postproc
        PROPERTIES IMPORTED_LOCATION
        ${LIBRARY_SOURCE_DIR}/ffmpeg/libpostproc.so
)

add_library(swresample SHARED IMPORTED)
set_target_properties(
        swresample
        PROPERTIES IMPORTED_LOCATION
        ${LIBRARY_SOURCE_DIR}/ffmpeg/libswresample.so
)

add_library(swscale SHARED IMPORTED)
set_target_properties(
        swscale
        PROPERTIES IMPORTED_LOCATION
        ${LIBRARY_SOURCE_DIR}/ffmpeg/libswscale.so
)

find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

add_subdirectory(simple_gme)

target_link_libraries( # Specifies the target library.
        native-lib
        avformat avcodec avfilter avutil swresample swscale postproc
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        z)