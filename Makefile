all:
	cd android; ndk-build
	cd android; ant debug;
	cd android/bin; adb install -r MarbleMachine-debug.apk && adb shell am start -a android.intent.action.MAIN -n net.leifandersen.mobile.android.marblemachine/.MainActivity

clean:
	cd android; ndk-build clean
	cd android; rm -r obj; rm -r libs;
	cd android; rm -r bin