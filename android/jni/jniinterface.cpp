#include <jni.h>
#include <string>

#include "nv_sound.h"
#include "nv_thread.h"
#include "nv_apk_file.h"
#include "nv_file.h"

#include "main.h"

using namespace std;

extern "C"
{
JNIEXPORT jint JNICALL
JNI_OnLoad (JavaVM * vm, void * reserved)
{
    NVThreadInit(vm);
    NvSoundInit();
    NvFInit();
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_initGL(JNIEnv * env, jobject obj)
{
    initGL();
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_updateGL(JNIEnv * env, jobject obj, jint width, jint height)
{
    updateGL(width, height);
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_draw(JNIEnv * env, jobject obj)
{
    draw();
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_touch(JNIEnv * env, jobject obj, jint finger, jfloat x, jfloat y)
{
    touch(finger, x, y);
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_move(JNIEnv * env, jobject obj, jint finger, jfloat x, jfloat y)
{
    move(finger, x, y);
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_release(JNIEnv * env, jobject obj, jint finger, jboolean canceled)
{
    release(finger, canceled);
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_pauseGame(JNIEnv * env, jobject obj)
{
    pauseGame();
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_resumeGame(JNIEnv * env, jobject obj)
{
    startGame();
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_restartGame(JNIEnv * env, jobject obj)
{
    // Currently do nothing
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_startGame(JNIEnv * env, jobject obj)
{
    setupGame();
}

JNIEXPORT void JNICALL
Java_net_leifandersen_mobile_android_marblemachine_MainLib_stopGame(JNIEnv * env, jobject obj)
{
    stopGame();
}
}
