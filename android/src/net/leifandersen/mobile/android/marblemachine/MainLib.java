package net.leifandersen.mobile.android.marblemachine;

public class MainLib {
    static {
        System.loadLibrary("jniinterface");
    }
    
    public static native void init(int width, int height);
    public static native void draw();
    public static native void touch(int finger, int x, int y);
    public static native void release(int finger);
}
