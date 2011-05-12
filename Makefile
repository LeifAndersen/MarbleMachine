all:
	./build-android

clean:
	cd android; ndk-build clean
	cd android; rm -r obj; rm -r libs;
	cd android; rm -r bin
