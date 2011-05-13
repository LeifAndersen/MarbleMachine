package net.leifandersen.mobile.android.marblemachine;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;

public class MainActivity extends Activity {

    MainView mView;
    static Context mContext;
    
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mView = new MainView(getApplication());
        setContentView(mView);
        mContext = this;
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
    
    public static Context getContext() {
        return mContext;
    }
}
