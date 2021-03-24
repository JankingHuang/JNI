package com.example.jniproject;

public class FromJNI {

    static {
        System.loadLibrary("native-lib");
    }
    private  int number = 3;

    public native int upDateObjProperty();
}
