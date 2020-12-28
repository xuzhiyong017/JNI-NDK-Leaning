package com.example.jni_ndk_learning;

import android.app.Application;

/**
 * @author: xuzhiyong
 * @date: 20-9-4  上午9:41
 * @Email: 18971269648@163.com
 * @description:
 */
public class App extends Application {

    static {
//        System.loadLibrary("native-lib");
//        System.loadLibrary("test-lib");
    }

    @Override
    public void onCreate() {
        super.onCreate();

    }
}
