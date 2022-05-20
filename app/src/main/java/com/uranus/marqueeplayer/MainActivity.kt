package com.uranus.marqueeplayer

import android.Manifest
import android.content.Intent
import android.content.pm.PackageManager
import android.opengl.GLSurfaceView
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.util.Log
import android.widget.TextView
import androidx.annotation.RequiresApi
import androidx.camera.core.CameraSelector
import androidx.camera.core.Preview
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.camera.view.PreviewView
import androidx.core.content.ContextCompat
import androidx.lifecycle.LifecycleOwner
import com.uranus.marqueeplayer.camera.CameraUtils
import com.uranus.marqueeplayer.camera.CameraView
import com.uranus.marqueeplayer.core.MarqueePlayer
import java.io.File
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MainActivity : AppCompatActivity(), GLSurfaceView.Renderer {
    @RequiresApi(Build.VERSION_CODES.M)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            requestPermissions(arrayOf(Manifest.permission.CAMERA,
                Manifest.permission.MOUNT_UNMOUNT_FILESYSTEMS,
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.READ_EXTERNAL_STORAGE), 1)

            var ret = checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE)
            if (ret == PackageManager.PERMISSION_GRANTED) {
                Log.d("marquee_", "WRITE_EXTERNAL_STORAGE PERMISSION_GRANTED")
            }

            ret = checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE)
            if (ret == PackageManager.PERMISSION_GRANTED) {
                Log.d("marquee_", "WRITE_EXTERNAL_STORAGE PERMISSION_GRANTED")
                m()
            }
        } else {
            m()
        }

        setContentView(R.layout.activity_main)
        CameraUtils.bindPreviewUseCase(this,
            findViewById<CameraView>(R.id.view_finder_2).surfaceProvider
            )

    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == 1) {
            m()
        }
    }

    fun m() {
        val f = File("mnt/sdcard/Android/VID_20220418_182423.mp4")
        Log.d("marquee_", "" + f.exists())
        MarqueePlayer(f.absolutePath);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
        }
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        TODO("Not yet implemented")
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        TODO("Not yet implemented")
    }

    override fun onDrawFrame(gl: GL10?) {
        TODO("Not yet implemented")
    }
}