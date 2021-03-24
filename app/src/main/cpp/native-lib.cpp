#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jniproject_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++12";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jniproject_MainActivity_SayHello(JNIEnv *env, jobject thiz) {
    // TODO: implement SayHello()
    std::string hello = "Hello NDK12";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jniproject_MainActivity_SayHelloFromStatic(JNIEnv *env, jclass clazz) {
    // TODO: implement SayHelloFromStatic()
    std::string  hello = "hello NDK static";
    return env->NewStringUTF(hello.c_str());
}
const  jint COUNT = 10;
extern "C" JNIEXPORT jint JNICALL
Java_com_example_jniproject_MainActivity_updateObjProperty(JNIEnv *env, jobject thiz) {
//    // TODO: implement updateObjProperty()
    jclass jclass1 = env->GetObjectClass(thiz);
    jfieldID jfieldId = env->GetFieldID(jclass1,"number","I");
    // jclass jIntClass = env->FindClass("java/lang/Integer");
    // jint 不能赋值给 jobject
    // 注意区分，Java 中的 int 和 Integer，JNI 是不会自动装箱和拆箱的
    // valueOf 入参是 int ，返回值为 Integer
    // jmethodID valueOf = env->GetStaticMethodID(jIntClass, "valueOf", "(I)Ljava/lang/Integer;");
    // jobject v = env->CallStaticObjectMethod(jIntClass, valueOf, COUNT);


    env->SetIntField(thiz,jfieldId,COUNT);

    jint value = env->GetIntField(thiz,jfieldId);

    env->DeleteLocalRef(jclass1);

    return value;


}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jniproject_MainActivity_invokeObjMethod(JNIEnv *env, jobject thiz) {
    // TODO: implement invokeObjMethod()
    jclass jclass1 = env->GetObjectClass(thiz);
    jmethodID  jmid = env->GetMethodID(jclass1, "methodForJNI",
            "(I)Ljava/lang/String;");
    //(I) 函数参数类型， java/lang/String 描述符（对应原函数的返回类型）
    env->DeleteLocalRef(jclass1);
    return static_cast<jstring>(env->CallObjectMethod(thiz, jmid, COUNT));
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_jniproject_MainActivity_createObj(JNIEnv *env,
        jobject){
    jclass  jclass1 = env->FindClass("com/example/jniproject/User");
    jmethodID jmid = env->GetMethodID(jclass1, "<init>", "(Ljava/lang/String;)V");
    jstring username = env->NewStringUTF("Janking");
    jobject user = env->NewObject(jclass1,jmid,username);
    env->DeleteLocalRef(jclass1);
    return user;
}extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_jniproject_MainActivity_getIntArray(JNIEnv *env, jobject thiz) {
    // TODO: implement getIntArray()
    jintArray _intArray = env->NewIntArray(COUNT);
    jint tmpArray[COUNT];
    for(jint i = 0; i < COUNT; i++){
        tmpArray[i] = i;
    }
    env->SetIntArrayRegion(_intArray,0,COUNT,tmpArray);
    return _intArray;
}
const int VALUE = 100;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jniproject_MainActivity_updateIntArray(JNIEnv *env, jobject thiz,
                                                        jintArray array) {
    // TODO: implement updateIntArray()
    jboolean  isCopy = static_cast<jboolean>(false);
    jint *arr = env->GetIntArrayElements(array , &isCopy);
    jint length = env->GetArrayLength(array);
    arr[0] = VALUE;

    env->SetIntArrayRegion(array, 0, length, arr);
    env->ReleaseIntArrayElements(array, arr, JNI_ABORT);

}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_jniproject_MainActivity_equals(JNIEnv *env, jobject thiz, jobject user1,
                                                jobject user2) {
    // TODO: implement equals()
    return  env->IsSameObject(user1,user2);
}
jobject  holdObj = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jniproject_MainActivity_holdUser(JNIEnv *env, jobject thiz, jobject user) {
    // TODO: implement holdUxser()
    //holdObj = user; error
    holdObj = env->NewGlobalRef(user);

    //JNI 通过 NewGlobalRef 和 DeleteGlobalRef 方法来创建全局引用和删除全局引用：
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jniproject_MainActivity_gcTest(JNIEnv *env, jobject thiz) {
    // TODO: implement gcTest()
    jclass  jclass1 = env->GetObjectClass(holdObj);
    jmethodID jmid = env->GetMethodID(jclass1,"getUsername","()Ljava/lang/String;");
    env->DeleteLocalRef(jclass1);
    return (jstring) env->CallObjectMethod(holdObj, jmid);
}