package com.example.jni_ndk_learning;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.RemoteException;
import android.view.View;
import android.widget.TextView;

import com.example.jni_ndk_learning.R;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void jumpToBigBitmap(View view) {
        Bundle bundle = new Bundle();
        bundle.putBinder("bitmapBinder", new IMyAidlInterface.Stub() {
            @Override
            public Bitmap getBitmap() throws RemoteException {
                return BitmapFactory.decodeResource(getResources(),R.drawable.timg);
            }
        });
        startActivity(new Intent(this,ShowBitmapActivity.class).putExtra("bitmap",bundle));
    }
}
