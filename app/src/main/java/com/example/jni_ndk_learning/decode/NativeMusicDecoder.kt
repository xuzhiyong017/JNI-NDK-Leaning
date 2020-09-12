package com.example.jni_ndk_learning.decode

/**
 * @author: xuzhiyong
 * @date: 20-9-11  上午9:24
 * @Email: 18971269648@163.com
 * @description:
 */
class NativeMusicDecoder {

    external fun createMusicDecoder(path:String)
    external fun start()
    external fun pause()
    external fun release()
}