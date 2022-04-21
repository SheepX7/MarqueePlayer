package com.uranus.marqueeplayer.camera

import android.content.Context
import android.graphics.SurfaceTexture
import android.opengl.GLES20
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.util.Log
import android.view.Surface
import android.widget.FrameLayout
import androidx.camera.core.CameraSelector
import androidx.camera.core.ImageCapture
import androidx.camera.core.Preview
import androidx.camera.core.SurfaceRequest
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.core.content.ContextCompat
import androidx.lifecycle.LifecycleOwner
import com.google.common.util.concurrent.ListenableFuture
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class CameraView : GLSurfaceView, GLSurfaceView.Renderer, SurfaceTexture.OnFrameAvailableListener {

    constructor(context: Context) : super(context)
    constructor(context: Context, attributeSet: AttributeSet): super(context, attributeSet)

    init {
        setRenderer(this)
        renderMode = RENDERMODE_WHEN_DIRTY
    }

    private var cameraTextureId: Int = 0
    private var surfaceTexture: SurfaceTexture? = null

    var surfaceProvider: Preview.SurfaceProvider =
        Preview.SurfaceProvider { request: SurfaceRequest ->
            if (holder.surface.isValid) {
                val surface = Surface(surfaceTexture)
                request.provideSurface(surface, ContextCompat.getMainExecutor(context),
                    {
                    })
                Logger.i("holder.surface.isValid: ${holder.surface.isValid}")
            }
        }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        val ids = intArrayOf(0)
        GLES20.glGenTextures(1, ids, 0)
        cameraTextureId = ids[0]

        // create surface texture
        surfaceTexture = SurfaceTexture(cameraTextureId)
        surfaceTexture?.setOnFrameAvailableListener(this@CameraView)

    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        GLES20.glViewport(0,0, width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        GLES20.glClearColor(1f, 0f, 0f, 0f)
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT)

        // 更新纹理
        surfaceTexture?.updateTexImage();
    }

    override fun onFrameAvailable(surfaceTexture: SurfaceTexture?) {
        requestRender()
    }

    class Filter {

    }
}