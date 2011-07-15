SOURCE_DIRS = ./sdl ./core ./core/entities
SOURCES := $(subst ./,,$(wildcard $(SOURCE_DIRS:=/*.cpp)))
HEADERS := $(subst ./,,$(wildcard $(SOURCE_DIRS:=/*.h)))
OBJECTS := $(addprefix build-sdl/,$(SOURCES:.cpp=.o))
CXX = g++
CXXFLAGS = -Wall -pedantic -g -I./sdl -I./core/ -I./core/entities/
LDFLAGS = -lSDL -lSDL_mixer -lGL -lGLU

all:
	cd android; ndk-build NDK_DEBUG=1
	cd android; android update project --path . --name MarbleMachine -s
	cd android; ant debug
	cd android/bin; adb install -r MarbleMachine-debug.apk
	cd android/bin; adb shell am start -a android.intent.action.MAIN -n net.leifandersen.mobile.android.marblemachine/.MainActivity
	mkdir -p assets
	blender meshes/marble.blend -b -P tools/blender_exporter.py -- assets/marble.mp3
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

build-sdl/gravity_well: $(OBJECTS)
	$(CXX) -o build-sdl/gravity_well $(OBJECTS) $(LDFLAGS)
	mkdir -p assets
	blender meshes/marble.blend -b -P tools/blender_exporter.py -- assets/marble.mp3
	convert meshes/tex0.png meshes/tex0.bmp
	mv meshes/tex0.bmp assets/tex0.mp3

build-sdl/%.o: %.cpp $(HEADERS) Makefile
	mkdir -p $(dir $@)
	$(CXX) -o $@ $(CXXFLAGS) -c $<

