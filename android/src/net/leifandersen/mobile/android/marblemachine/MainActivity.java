package net.leifandersen.mobile.android.marblemachine;

import com.nvidia.devtech.AudioHelper;

import android.app.Activity;
import android.content.Context;
import android.drm.DrmStore.Action;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;
import android.os.Bundle;
import android.provider.MediaStore.Audio;
import android.util.Log;
import android.view.MotionEvent;

public class MainActivity extends Activity {

    MainView mView;
        
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        AudioHelper helper = AudioHelper.getInstance();
        helper.setContext(getApplicationContext());
        mView = new MainView(getApplication());
        setContentView(mView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mView.onResume();
    }
    
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        super.onTouchEvent(event);
        
        // Translate MotionEvent to internal calls
        int action = event.getActionMasked();
        
        switch(action) {
	        case MotionEvent.ACTION_DOWN:
	        	int firstPointer = action >> MotionEvent.ACTION_POINTER_ID_SHIFT;
	        	MainLib.touch(firstPointer, event.getX(firstPointer), event.getY(firstPointer));
	        	break;
	        	
	        case MotionEvent.ACTION_UP:
	        	int lastPointer = action >> MotionEvent.ACTION_POINTER_ID_SHIFT;
	        	MainLib.release(lastPointer, false);
	        	break;
	        	
	        case MotionEvent.ACTION_MOVE:
	        	for (int i = 0; i < event.getPointerCount(); i++) {
	        		MainLib.move(i, event.getX(i), event.getY(i));
	        	}
	        	break;
	        	
	        case MotionEvent.ACTION_CANCEL:
	        	// Canceled gesture, removing finger
	        	int canceledPointer = action >> MotionEvent.ACTION_POINTER_ID_SHIFT;
	        	MainLib.release(canceledPointer, true);
	        	break;
	        	
	        case MotionEvent.ACTION_OUTSIDE:
	        	// HACK -- Not sure this is the correct behavior.
	        	for (int i = 0; i < event.getPointerCount(); i++) {
	        		MainLib.move(i, event.getX(i), event.getY(i));
	        	}
	        	break;
	        	
	        case MotionEvent.ACTION_POINTER_DOWN:
	        	int newPointer = action >> MotionEvent.ACTION_POINTER_ID_SHIFT;
	        	MainLib.touch(newPointer, event.getX(newPointer), event.getY(newPointer));
	        	break;
	        	
	        case MotionEvent.ACTION_POINTER_UP:
	        	int currentPointer = action >> MotionEvent.ACTION_POINTER_ID_SHIFT;
	        	MainLib.release(currentPointer, false);
	        	break;
	        	
        	default: 
        		return false;
        }
        
        return true;
    }
    
}
