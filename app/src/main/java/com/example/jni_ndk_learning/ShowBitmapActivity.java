package com.example.jni_ndk_learning;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.os.Bundle;
import android.widget.ImageView;

public class ShowBitmapActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_show_bitmap);
        Bundle bundle = getIntent().getBundleExtra("bitmap");
        IMyAidlInterface aidlInterface = (IMyAidlInterface) bundle.getBinder("bitmapBinder");
        try {
            ((ImageView)findViewById(R.id.image_view)).setImageBitmap(aidlInterface.getBitmap());
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}