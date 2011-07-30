SOURCE_DIRS = ./sdl ./core ./core/entities
SOURCES := $(subst ./,,$(wildcard $(SOURCE_DIRS:=/*.cpp)))
HEADERS := $(subst ./,,$(wildcard $(SOURCE_DIRS:=/*.h)))
OBJECTS := $(addprefix build-sdl/,$(SOURCES:.cpp=.o))
CXX = g++
CXXFLAGS = -Wall -pedantic -g -I./include -I./sdl -I./core/ -I./core/entities/
LDFLAGS = -lSDL -lSDL_mixer -lGL -lGLU

all:build-sdl/gravity_well

android:android/bin/MarbleMachine-debug.apk
	rm -f android/bin/MarbleMachine-debug.apk

android/bin/MarbleMachine-debug.apk:assets/light_planet.mp3 assets/medium_planet.mp3 assets/heavy_planet.mp3 assets/anti_planet.mp3 assets/light_planet.mp3 assets/goal.mp3 assets/ship.mp3 assets/font.mp3 assets/galaxy.mp3
	cd android; ndk-build NDK_DEBUG=1
	cd android; android update project --path . --name MarbleMachine -s
	etc1tool --encodeNoHeader meshes/tex0.png
	mv meshes/tex0.pkm assets/tex0.mp3
	cd android; ant debug
	cd android/bin; adb install -r MarbleMachine-debug.apk
	cd android/bin; adb shell am start -a android.intent.action.MAIN -n net.leifandersen.mobile.android.marblemachine/.MainActivity

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

assets/galaxy.mp3:levels/galaxy.lvl tools/menu_exporter.py
	blender -b -P tools/menu_exporter.py -- levels/galaxy.lvl assets/galaxy.mp3
	blender -b -P tools/menu_exporter.py -- levels/sector_1.lvl assets/sector_1.mp3

assets/light_planet.mp3:meshes/light_planet.blend
	mkdir -p ${dir $@}
	blender $< -b -P tools/blender_exporter.py -- $@

assets/medium_planet.mp3:meshes/medium_planet.blend
	mkdir -p ${dir $@}
	blender $< -b -P tools/blender_exporter.py -- $@

assets/heavy_planet.mp3:meshes/heavy_planet.blend
	mkdir -p ${dir $@}
	blender $< -b -P tools/blender_exporter.py -- $@

assets/anti_planet.mp3:meshes/anti_planet.blend
	mkdir -p ${dir $@}
	blender $< -b -P tools/blender_exporter.py -- $@

assets/goal.mp3:meshes/goal.blend
	mkdir -p ${dir $@}
	blender $< -b -P tools/blender_exporter.py -- $@

assets/ship.mp3:meshes/ship.blend
	mkdir -p ${dir $@}
	blender $< -b -P tools/blender_exporter.py -- $@

assets/font.mp3:meshes/font.txt meshes/buttons.txt Makefile
	mkdir -p assets
	blender -b -P tools/font_exporter.py -- meshes/font.txt assets/font.mp3
	blender -b -P tools/button_exporter.py -- meshes/buttons.txt assets/

build-sdl/gravity_well: $(OBJECTS) assets/light_planet.mp3 assets/medium_planet.mp3 assets/heavy_planet.mp3 assets/anti_planet.mp3 assets/light_planet.mp3 assets/goal.mp3 assets/ship.mp3 assets/font.mp3 assets/galaxy.mp3
	$(CXX) -o build-sdl/gravity_well $(OBJECTS) $(LDFLAGS)
	convert meshes/tex0.png meshes/tex0.bmp
	mv meshes/tex0.bmp assets/tex0.mp3
	echo "Now run make install to put assets in proper locations."

build-sdl/%.o: %.cpp $(HEADERS) Makefile
	mkdir -p $(dir $@)
	$(CXX) -o $@ $(CXXFLAGS) -c $<
