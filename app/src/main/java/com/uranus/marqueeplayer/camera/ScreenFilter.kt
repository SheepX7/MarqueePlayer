package com.uranus.marqueeplayer.camera

import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer

class ScreenFilter {

    //顶点坐标
    private val VERTEX = floatArrayOf(
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
    )

    //纹理坐标
    private val TEXTURE = floatArrayOf(
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    )

    private val vertexBuffer: FloatBuffer
        get() = ByteBuffer
            .allocateDirect(4 * 4 * 2)
            .order(ByteOrder.nativeOrder())
            .asFloatBuffer()

    private val textureBuffer: FloatBuffer
        get() = ByteBuffer
            .allocateDirect(4 * 2 * 4)
            .order(ByteOrder.nativeOrder())
            .asFloatBuffer()

    init {
        vertexBuffer.clear()
        vertexBuffer.put(VERTEX)

        textureBuffer.clear()
        textureBuffer.put(TEXTURE)
    }

}