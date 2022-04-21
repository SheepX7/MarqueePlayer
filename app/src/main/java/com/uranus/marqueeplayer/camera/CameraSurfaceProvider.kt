package com.uranus.marqueeplayer.camera

import android.opengl.GLSurfaceView
import android.view.SurfaceHolder
import androidx.camera.core.Preview
import androidx.camera.core.SurfaceRequest

class CameraSurfaceProvider : Preview.SurfaceProvider{
    lateinit var glSurfaceView: GLSurfaceView

    override fun onSurfaceRequested(request: SurfaceRequest) {
        request.provideSurface(glSurfaceView.holder.surface, {}, {})
    }
}