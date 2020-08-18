package com.example.jni_ndk_learning;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static String[] getLibraries =  {
        "hidapi",
                "SDL2",
                // "SDL2_image",
                // "SDL2_mixer",
                // "SDL2_net",
                // "SDL2_ttf",
                "native-lib"
    };
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("hidapi");
        System.loadLibrary("SDL2");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        showStudentInfo(new Student("xuzhiyong",20));

        loadLibraries();
    }

    // Load the .so
    public void loadLibraries() {

    }

    public native void showStudentInfo(Student student);

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
