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
    
}
