package com.example.jniproject;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "Main";

    public  int number = 2;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        int number = 3;
        String str = null;
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);

        str += stringFromJNI() + "\n";

        str += SayHello() + "\n";

        str += SayHelloFromStatic() + "\n";

        str += updateObjProperty() + "\n";

        str += invokeObjMethod() + "\n";

        User user = createObj();
        str += "Native 创建 Java对象：";
        str += user.getUsername() + "\n";

        int[] array = {1, 2, 3, 4, 5};

        int[] arr = getIntArray();
        str += "从Native 获取int[]:";
        str += Arrays.toString(arr) + "\n";

        updateIntArray(array);
        str += Arrays.toString(array)+"\n";

        User user1 = new User("Kali");

        str += "判断对象 User1 与 User 是否相等:";
        str += equals(user1,user) + "\n";

        str += "判断对象 User 与 User是否相等:";
        str += equals(user,user) + "\n";

        holdUser(user1);

        str += "测试JNI GC：";
        str += gcTest()+"\n";

        tv.setText(str);


    }
    private String methodForJNI(int value){
        return "本地方法被 Native 调用，参数为，" + value;
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String SayHello();

    public native  static String SayHelloFromStatic();

    public native int updateObjProperty();

    public native String invokeObjMethod();

    public native User createObj();

    public native int[] getIntArray();

    public native void updateIntArray(int[] array);

    public native boolean equals(User user1, User user2);

    public native void holdUser(User user);

    public native String gcTest();

}