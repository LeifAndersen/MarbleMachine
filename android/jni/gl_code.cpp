#include <jni.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

extern "C" {
    JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_init(JNIEnv * env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_draw(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_touch(JNIEnv * env, jobject obj, jint finger, jint x, jint y);
    JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_release(JNIEnv * env, jobject obj, jint finger);
};

JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_init(JNIEnv * env, jobject obj, jint width, jint height)
{

}


JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_draw(JNIEnv * env, jobject obj)
{

}

JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_touch(JNIEnv * env, jobject obj, jint finger, jint x, jint y)
{

}

JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_release(JNIEnv * env, jobject obj, jint finger)
{

}
