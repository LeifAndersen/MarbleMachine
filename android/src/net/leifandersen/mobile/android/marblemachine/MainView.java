package net.leifandersen.mobile.android.marblemachine;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class MainView extends GLSurfaceView {

    public MainView(Context context) {
        super(context);
        
        setRenderer(new Renderer());
    }
    
    private static class Renderer implements GLSurfaceView.Renderer {
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            
        }
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            MainLib.init(width, height);
        }
        public void onDrawFrame(GL10 gl) {
            MainLib.draw();
        }
    }
}
