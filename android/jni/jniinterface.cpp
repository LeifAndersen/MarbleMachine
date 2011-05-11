#include <jni.h>
#include <string>

#include "../../core/main.h"

using namespace std;

extern "C"
{
    JNIEXPORT void JNICALL
    Java_net_leifandersen_mobile_android_marblemachine_MainLib_init(JNIEnv * env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL
    Java_net_leifandersen_mobile_android_marblemachine_MainLib_draw(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL
    Java_net_leifandersen_mobile_android_marblemachine_MainLib_touch(JNIEnv * env, jobject obj, jint finger, jint x, jint y);
    JNIEXPORT void JNICALL
    Java_net_leifandersen_mobile_android_marblemachine_MainLib_move(JNIEnv * env, jobject obj, jint finger, jint x, jint y);
    JNIEXPORT void JNICALL
    Java_net_leifandersen_mobile_android_marblemachine_MainLib_release(JNIEnv * env, jobject obj, jint finger);
    JNIEXPORT void JNICALL
    Java_net_leifandersen_mobile_android_marblemachine_MainLib_pauseGame(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL
    Java_net_leifandersen_mobile_android_marblemachine_MainLib_resumeGame(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL
    Java_net_leifandersen_mobile_android_marblemachine_MainLib_resetGame(JNIEnv * env, jobject obj);
    JNIEXPORT jstring JNICALL
    Java_net_leifandersen_mobile_android_marblemachine_MainLib_getMusic(JNIEnv * env, jobject obj);
    JNIEXPORT jstring JNICALL
    Java_net_leifandersen_mobile_android_marblemachine_MainLib_getSound(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_init(JNIEnv * env, jobject obj, jint width, jint height)
{
    init(width, height);
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_draw(JNIEnv * env, jobject obj)
{
    draw();
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_touch(JNIEnv * env, jobject obj, jint finger, jint x, jint y)
{
    touch(finger, x, y);
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_move(JNIEnv * env, jobject obj, jint finger, jint x, jint y)
{
    move(finger, x, y);
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_release(JNIEnv * env, jobject obj, jint finger)
{
    release(finger);
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_pauseGame(JNIEnv * env, jobject obj)
{
    pauseGame();
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_resumeGame(JNIEnv * env, jobject obj)
{
    resumeGame();
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_resetGame(JNIEnv * env, jobject obj)
{
    resetGame();
}

JNIEXPORT jstring JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_getMusic(JNIEnv * env, jobject obj)
{
    return env->NewStringUTF(getMusic().c_str());
}

JNIEXPORT jstring JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_getSound(JNIEnv * env, jobject obj)
{
    return env->NewStringUTF(getSound().c_str());
}
