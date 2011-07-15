SOURCE_DIRS = ./sdl ./core ./core/entities
SOURCES := $(subst ./,,$(wildcard $(SOURCE_DIRS:=/*.cpp)))
HEADERS := $(subst ./,,$(wildcard $(SOURCE_DIRS:=/*.h)))
OBJECTS := $(addprefix build-sdl/,$(SOURCES:.cpp=.o))
CXX = g++
SDL_BUILD_DIR = build-sdl
CXXFLAGS = -Wall -pedantic -g -I./include -I./sdl -I./core/ -I./core/entities/ -I./$(SDL_BUILD_DIR)/lib
LDFLAGS = -L$(SDL_BUILD_DIR)/lib -lSDL -lSDL_mixer -lSDL_image -lGL -lGLU
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
	rm -rf assets
	rm -rf bin
	rm -rf include
	rm -rf lib
	rm -rf share

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

$(SDL_BUILD_DIR)/gravity_well: $(OBJECTS) assets/marble.mp3 assets/font.mp3
	$(CXX) -o $(SDL_BUILD_DIR)/gravity_well $(OBJECTS) $(LDFLAGS)
	convert meshes/tex0.png meshes/tex0.bmp
	mv meshes/tex0.bmp assets/tex0.mp3

$(SDL_BUILD_DIR)/%.o: %.cpp $(HEADERS) Makefile $(SDL_BUILD_DIR)/lib/libSDL.a $(SDL_BUILD_DIR)/lib/libSDL_mixer.a $(SDL_BUILD_DIR)/lib/libSDL_image.a
	mkdir -p $(dir $@)
	$(CXX) -o $@ $(CXXFLAGS) -c $<

$(SDL_BUILD_DIR)/lib/libSDL.a: Makefile
	mkdir -p $(SDL_BUILD_DIR)
	cd libraries/SDL-1.2.14; ./configure --prefix=`pwd`/../../$(SDL_BUILD_DIR)
	cd libraries/SDL-1.2.14; make; make install


$(SDL_BUILD_DIR)/lib/libSDL_mixer.a:$(SDL_BUILD_DIR)/lib/libSDL.a Makefile
	cd libraries/SDL_mixer-1.2.11; ./autogen.sh; ./configure --prefix=`pwd`/../../$(SDL_BUILD_DIR) --with-sdl-prefix=`pwd`/../../$(SDL_BUILD_DIR)
	cd libraries/SDL_mixer-1.2.11; make; make install

$(SDL_BUILD_DIR)lib/libSDL_image.a:$(SDL_BUILD_DIR)/lib/libSDL.a Makefile
	cd libraries/SDL_image-1.2.10; ./autogen.sh; ./configure --prefix=`pwd`/../../$(SDL_BUILD_DIR) --with-sdl-prefix=`pwd`/../../$(SDL_BUILD_DIR)
	cd libraries/SDL_image-1.2.10; make; make install
