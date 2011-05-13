package net.leifandersen.mobile.android.marblemachine;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {

    MainView mView;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        MainLib.initAudio();
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
