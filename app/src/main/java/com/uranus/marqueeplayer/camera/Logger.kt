package com.uranus.marqueeplayer.camera

import android.graphics.Camera
import android.util.Log

object Logger {

    private const val CAMERA = "@camera"

    fun i(str: String, vararg arg: String) {
        Log.i(CAMERA, String.format(str, *arg))
    }

}