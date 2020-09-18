package com.example.jni_ndk_learning

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.view.SurfaceHolder
import com.example.jni_ndk_learning.decode.NativePlayer
import kotlinx.android.synthetic.main.activity_video_player.*

class VideoPlayerActivity : AppCompatActivity() {

    val player = NativePlayer()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_video_player)
        surfaceView.holder.addCallback(object :SurfaceHolder.Callback{
            override fun surfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {

            }

            override fun surfaceDestroyed(holder: SurfaceHolder?) {

            }

            override fun surfaceCreated(holder: SurfaceHolder?) {
                holder?.run {
                    player.createPlayer(Environment.getExternalStorageDirectory().absolutePath+"/one_piece.mp4",surface);
                    player.start()
                }

            }
        })
    }


    override fun onPause() {
        super.onPause()
        player.pause();
    }

    override fun onDestroy() {
        super.onDestroy()
        player.release()
    }
}