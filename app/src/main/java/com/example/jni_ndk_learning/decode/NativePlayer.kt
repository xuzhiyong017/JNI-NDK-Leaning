package com.example.jni_ndk_learning.decode

import android.view.Surface

/**
 * @author: xuzhiyong
 * @date: 20-9-16  下午5:37
 * @Email: 18971269648@163.com
 * @description:
 */
class NativePlayer {
    external fun createPlayer(path:String,surface: Surface);
    external fun start();
    external fun pause();
    external fun release();
}