package com.example.jni_ndk_learning;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.example.jni_ndk_learning.R;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private String name = "hello";

    static {
        System.loadLibrary("test-lib");
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        findViewById(R.id.sample_text_2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                changeName1(BitmapFactory.decodeResource(getResources(),R.drawable.test_123));
                ((TextView)findViewById(R.id.sample_text_2)).setText(name);
            }
        });
        ((TextView)findViewById(R.id.sample_text_2)).setText(name);

    }

    public native void changeName();
    public static native void changeName1(Bitmap bitmap);


    class Student{
        String name;
        int age;

        public Student(String name, int age) {
            this.name = name;
            this.age = age;
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

}
