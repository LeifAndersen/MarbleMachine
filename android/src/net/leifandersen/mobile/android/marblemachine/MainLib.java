package net.leifandersen.mobile.android.marblemachine;

public class MainLib {
    static {
        System.loadLibrary("Foo");
    }
    
    public static native void init(int width, int height);
}
