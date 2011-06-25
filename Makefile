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
	cd android; rm -r obj; rm -r libs;
	cd android; rm -r bin

sdl:build-sdl/marble_machine

build-sdl/marble_machine: $(OBJECTS)
	$(CXX) -o build-sdl/marble_machine $(OBJECTS) $(LDFLAGS)

build-sdl/%.o: %.cpp $(HEADERS) Makefile
	mkdir -p $(dir $@)
	$(CXX) -o $@ $(CXXFLAGS) -c $<

