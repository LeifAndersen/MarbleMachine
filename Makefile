SOURCE_DIRS = ./sdl ./core ./core/entities
SOURCES := $(subst ./,,$(wildcard $(SOURCE_DIRS:=/*.cpp)))
HEADERS := $(subst ./,,$(wildcard $(SOURCE_DIRS:=/*.h)))
OBJECTS := $(addprefix build-sdl/,$(SOURCES:.cpp=.o))
CXX = g++
CXXFLAGS = -Wall -pedantic -g -I./sdl -I./core/ -I./core/entities/
LDFLAGS = -lSDL -lGL -lGLU

all:
	cd android; ndk-build NDK_DEBUG=1
	cd android; android update project --path . --name MarbleMachine -s
	cd android; ant debug
	cd android/bin; adb install -r MarbleMachine-debug.apk
	cd android/bin; adb shell am start -a android.intent.action.MAIN -n net.leifandersen.mobile.android.marblemachine/.MainActivity

clean:
	cd android; ndk-build clean
	cd android; rm -rf obj; rm -rf libs;
	cd android; rm -rf bin
	rm -rf ~/gravity_well
	rm -rf build-sdl

install:
	rm -rf ~/gravity_well
	mkdir -p ~/gravity_well
	cp build-sdl/gravity_well ~/gravity_well/gravity_well
	cp -r assets/ ~/gravity_well/data

sdl:build-sdl/gravity_well

build-sdl/gravity_well: $(OBJECTS)
	$(CXX) -o build-sdl/gravity_well $(OBJECTS) $(LDFLAGS)

build-sdl/%.o: %.cpp $(HEADERS) Makefile
	mkdir -p $(dir $@)
	$(CXX) -o $@ $(CXXFLAGS) -c $<

