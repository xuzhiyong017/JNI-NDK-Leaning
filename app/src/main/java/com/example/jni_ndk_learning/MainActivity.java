package com.example.jni_ndk_learning;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.app.ActivityManager;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.example.jni_ndk_learning.R;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(getFFmpegInfo());


    }

    public native  String getFFmpegInfo();

    public void touchButton(View view) {
        for (int i = 0; i < 1; i++) {
            Toast.makeText(this,"touchButton",Toast.LENGTH_SHORT).show();
        }
    }


    class Student{
        String name;
        int age;

        public Student(String name, int age) {
            this.name = name;
            this.age = age;
        }
    }

}
