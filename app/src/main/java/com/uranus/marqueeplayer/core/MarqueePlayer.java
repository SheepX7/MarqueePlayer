package com.uranus.marqueeplayer.core;

public class MarqueePlayer {

    static {
        System.loadLibrary("native-lib");
    }

    public MarqueePlayer(String path) {
        native_open(path);
    }

    native void native_open(String path);
}
