package net.leifandersen.mobile.android.marblemachine;

import com.nvidia.devtech.AudioHelper;

import android.app.Activity;
import android.content.Context;
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
        int action = event.getAction() & MotionEvent.ACTION_MASK;
        
        /*
         * The event type enum for reference
         * 0 "ACTION_DOWN"
         * 1 "ACTION_UP"
         * 2 "ACTION_MOVE"
         * 3 "ACTION_CANCEL"
         * 4 "ACTION_OUTSIDE"
         * 5 "ACTION_POINTER_DOWN"
         * 6 "ACTION_POINTER_UP"
         */
        switch(action) {
	        case 0:
	        	int firstPointer = action >> MotionEvent.ACTION_POINTER_ID_SHIFT;
	        	MainLib.touch(firstPointer, event.getX(firstPointer), event.getY(firstPointer));
	        	break;
	        	
	        case 1:
	        	int lastPointer = action >> MotionEvent.ACTION_POINTER_ID_SHIFT;
	        	MainLib.release(lastPointer, false);
	        	break;
	        	
	        case 2:
	        	for (int i = 0; i < event.getPointerCount(); i++) {
	        		MainLib.move(i, event.getX(i), event.getY(i));
	        	}
	        	break;
	        	
	        case 3:
	        	// Canceled gesture, removing finger
	        	int canceledPointer = action >> MotionEvent.ACTION_POINTER_ID_SHIFT;
	        	MainLib.release(canceledPointer, true);
	        	break;
	        	
	        case 4:
	        	// HACK -- Not sure this is the correct behavior.
	        	for (int i = 0; i < event.getPointerCount(); i++) {
	        		MainLib.move(i, event.getX(i), event.getY(i));
	        	}
	        	break;
	        	
	        case 5:
	        	int newPointer = action >> MotionEvent.ACTION_POINTER_ID_SHIFT;
	        	MainLib.touch(newPointer, event.getX(newPointer), event.getY(newPointer));
	        	break;
	        	
	        case 6:
	        	int currentPointer = action >> MotionEvent.ACTION_POINTER_ID_SHIFT;
	        	MainLib.release(currentPointer, false);
	        	break;
	        	
        	default: 
        		return false;
        }
        
        return true;
    }
    
}
