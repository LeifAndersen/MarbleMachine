SOURCE_DIRS = ./sdl ./core ./core/entities
SOURCES := $(subst ./,,$(wildcard $(SOURCE_DIRS:=/*.cpp)))
HEADERS := $(subst ./,,$(wildcard $(SOURCE_DIRS:=/*.h)))
OBJECTS := $(addprefix build-sdl/,$(SOURCES:.cpp=.o))
CXX = g++
CXXFLAGS = -Wall -pedantic -g -I./include -I./sdl -I./core/ -I./core/entities/
LDFLAGS = -lSDL -lSDL_mixer -lSDL_image -lGL -lGLU
SDL_CFLAGS = $(shell ./bin/sdl-config --cflags)
SDL_LDFLAGS = $(shell ./bin/sdl-config --libs) -lSDL -lSDL_mixer -lSDL_image

all:assets/marble.mp3 assets/font.mp3
	cd android; ndk-build NDK_DEBUG=1
	cd android; android update project --path . --name MarbleMachine -s
	cd android; ant debug
	cd android/bin; adb install -r MarbleMachine-debug.apk
	cd android/bin; adb shell am start -a android.intent.action.MAIN -n net.leifandersen.mobile.android.marblemachine/.MainActivity
	etc1tool --encodeNoHeader meshes/tex0.png
	mv meshes/tex0.pkm assets/tex0.mp3
clean:
	cd android; ndk-build clean
	cd android; rm -rf obj; rm -rf libs;
	cd android; rm -rf bin
	rm -rf ~/gravity_well
	rm -rf build-sdl
	rm -rf assets/

install:
	rm -rf ~/gravity_well
	mkdir -p ~/gravity_well
	cp build-sdl/gravity_well ~/gravity_well/gravity_well
	cp -r assets/ ~/gravity_well/data

sdl:build-sdl/gravity_well

assets/marble.mp3:meshes/marble.blend
	mkdir -p assets
	blender meshes/marble.blend -b -P tools/blender_exporter.py -- assets/marble.mp3

assets/font.mp3:meshes/font.txt
	mkdir -p assets
	blender -b -P tools/font_exporter.py -- meshes/font.txt assets/font.mp3

build-sdl/gravity_well: $(OBJECTS) assets/marble.mp3 assets/font.mp3
	$(CXX) -o build-sdl/gravity_well $(OBJECTS) $(LDFLAGS)
	convert meshes/tex0.png meshes/tex0.bmp
	mv meshes/tex0.bmp assets/tex0.mp3

build-sdl/%.o: %.cpp $(HEADERS) Makefile lib/libSDL.a lib/libSDL_mixer.a lib/libSDL_image.a lib/libSDL_net.a
	mkdir -p $(dir $@)
	$(CXX) -o $@ $(CXXFLAGS) -c $<

lib/libSDL.a: Makefile
	cd libraries/SDL-1.2.14; ./configure --prefix=`pwd`/../..
	cd libraries/SDL-1.2.14; make; make install


lib/libSDL_mixer.a:lib/libSDL.a Makefile
	cd libraries/SDL_mixer-1.2.11; ./autogen.sh; ./configure --prefix=`pwd`/../.. --with-sdl-prefix=`pwd`/../..
	cd libraries/SDL_mixer-1.2.11; make; make install

lib/libSDL_image.a:lib/libSDL.a Makefile
	cd libraries/SDL_image-1.2.10; ./autogen.sh; ./configure --prefix=`pwd`/../.. --with-sdl-prefix=`pwd`/../..
	cd libraries/SDL_image-1.2.10; make; make install lib/libSDL_net.a:lib/libSDL.a

lib/libSDL_net.a:lib/libSDL.a Makefile
	cd libraries/SDL_net-1.2.7; ./autogen.sh; ./configure --prefix=`pwd`/../.. --with-sdl-prefix=`pwd`/../..
	cd libraries/SDL_net-1.2.7; make; make install
