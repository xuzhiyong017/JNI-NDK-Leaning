package com.example.jni_ndk_learning;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.app.ActivityManager;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.example.jni_ndk_learning.R;

public class MainActivity extends AppCompatActivity {

    TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        tv = findViewById(R.id.sample_text);
    }

    public void touchButton(View view) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                tv.setText("我的子线程"+Thread.currentThread().getName()+"");
            }
        }).start();
    }



}
