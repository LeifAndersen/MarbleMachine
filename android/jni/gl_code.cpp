#include <jni.h>

extern "C" {
    JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_init(JNIEnv * env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_draw(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_init(JNIEnv * env, jobject obj, jint width, jint height)
{

}


JNIEXPORT void JNICALL Java_net_leifandersen_mobile_android_marblemachine_MainLib_draw(JNIEnv * env, jobject obj)
{

}
