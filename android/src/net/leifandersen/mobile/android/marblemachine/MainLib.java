package net.leifandersen.mobile.android.marblemachine;

public class MainLib {
    static {
        System.loadLibrary("jniinterface");
    }
    
    public static native void init(int width, int height);
    public static native void draw();
}
