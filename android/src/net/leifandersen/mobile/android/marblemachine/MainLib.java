package net.leifandersen.mobile.android.marblemachine;

public class MainLib {
    static {
        System.loadLibrary("jniinterface");
    }
    
    public static native void initGL();
    public static native void updateGL(int width, int height);
    public static native void draw();

    public static native void touch(int finger, int x, int y);
    public static native void move(int finger, int x, int y);
    public static native void release(int finger);

    public static native void pauseGame();
    public static native void resumeGame();
    public static native void resetGame();
}
