package com.uranus.marqueeplayer.camera

import android.content.Context
import android.util.Log
import androidx.camera.core.CameraSelector
import androidx.camera.core.Preview
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.core.content.ContextCompat
import androidx.lifecycle.LifecycleOwner

object CameraUtils {
    fun bindPreviewUseCase(context: Context, surfaceProvider: Preview.SurfaceProvider) {
        var cameraProviderFuture = ProcessCameraProvider.getInstance(context)
        cameraProviderFuture.addListener(
            {
                var cameraProvider = cameraProviderFuture.get()

                var preView = Preview.Builder().build()

                var cameraSelector = CameraSelector.Builder()
                    .requireLensFacing(CameraSelector.LENS_FACING_BACK)
                    .build()

                var camera = cameraProvider.bindToLifecycle(
                    (context as LifecycleOwner), cameraSelector, preView
                )

                preView.setSurfaceProvider {
                    Log.i("@CameraX", "camera request surface")
                    surfaceProvider.onSurfaceRequested(it)
                }
            },
            ContextCompat.getMainExecutor(context)
        )
    }
}