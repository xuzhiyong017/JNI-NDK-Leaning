package com.example.jni_ndk_learning

import android.app.Service
import android.content.Intent
import android.os.IBinder

/**
 * @author: xuzhiyong
 * @date: 20-9-7  上午10:22
 * @Email: 18971269648@163.com
 * @description:
 */
class MyServer : Service() {

    override fun onBind(p0: Intent?): IBinder? {
       return null
    }
}