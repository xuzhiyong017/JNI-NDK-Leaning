package com.example.jni_ndk_learning

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.view.View
import android.widget.SeekBar
import com.example.jni_ndk_learning.decode.NativeMusicDecoder
import kotlinx.android.synthetic.main.activity_music_decode.*

class MusicDecodeActivity : AppCompatActivity() {

    var musicDecoder:NativeMusicDecoder = NativeMusicDecoder()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_music_decode)
//        musicDecoder.createMusicDecoder(tv_path.text.toString())
        musicDecoder.createMusicDecoder(Environment.getExternalStorageDirectory().absolutePath+"/123.mp3")

        seek_bar.setOnSeekBarChangeListener(object :SeekBar.OnSeekBarChangeListener{
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                musicDecoder.setVolume(progress)
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {

            }

            override fun onStopTrackingTouch(seekBar: SeekBar?) {

            }
        })
    }

    fun startDecoder(view: View) {
        musicDecoder.start()
    }

    override fun onStop() {
        super.onStop()

    }

    override fun onDestroy() {
        super.onDestroy()
        musicDecoder.release()
    }

    fun pauseDecoder(view: View) {
        musicDecoder.pause()
    }
}