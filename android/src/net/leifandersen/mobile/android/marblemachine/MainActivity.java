package net.leifandersen.mobile.android.marblemachine;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;

import com.nvidia.devtech.AudioHelper;
import com.nvidia.devtech.NvAPKFileHelper;

public class MainActivity extends Activity {

    MainView mView;
        
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Set up audio helper's context
        AudioHelper helper = AudioHelper.getInstance();
        helper.setContext(getApplicationContext());
        
        // Set up the apk file helper's context
        NvAPKFileHelper apkHelper = NvAPKFileHelper.getInstance();
        apkHelper.setContext(this);
        
        // create a view and set it as the main view
        mView = new MainView(getApplication());
        setContentView(mView);
        //setContentView(R.layout.main);
        // create the game
        MainLib.createGame();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        MainLib.destroyGame();
    }


    @Override
    protected void onPause() {
        super.onPause();
        MainLib.pauseGame();
        mView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        MainLib.resumeGame();
        mView.onResume();
    }
    
    
    @Override
    protected void onStart() {
        super.onStart();
        MainLib.startGame();
    }
    
    @Override
    protected void onRestart() {
        super.onRestart();
        MainLib.restartGame();
    }
    
    @Override
    protected void onStop() {
        super.onStop();
        MainLib.stopGame();
    }
    
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        super.onTouchEvent(event);
        
        // Translate MotionEvent to internal calls
        int action = event.getAction() & MotionEvent.ACTION_MASK;
        
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
