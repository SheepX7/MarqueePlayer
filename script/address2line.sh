#!/bin/sh
echo "aarch64-linux-android-addr2line -f -C -e $1 $2" >> echo.txt
aarch64-linux-android-addr2line -e ../app/build/intermediates/cmake/debug/obj/arm64-v8a/lib$1.so