package net.leifandersen.mobile.android.marblemachine;

public class MainLib {
    static {
        System.loadLibrary("jniinterface");
    }
    
    public static native void initGL();
    public static native void updateGL(int width, int height);
    public static native void draw();

    public static native void touch(int finger, float x, float y);
    public static native void move(int finger, float x, float y);
    public static native void release(int finger, boolean canceled);

    public static native void pauseGame();
    public static native void resumeGame();
    public static native void restartGame();
    public static native void startGame();
    public static native void stopGame();
}
