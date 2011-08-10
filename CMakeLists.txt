cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "-g -Wall")
project(gravity_well)

find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL_image REQUIRED)
find_package(OpenGL REQUIRED)

if(NOT SDL_FOUND)
    message ( FATAL_ERROR "SDL not found!")
endif(NOT SDL_FOUND)

link_libraries(
    ${SDL_LIBRARY}
    ${SDLMIXER_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    SDLmain
    ${OPENGL_LIBRARY}
    core
)

include_directories("${PROJECT_SOURCE_DIR}/sdl")
include_directories("${PROJECT_SOURCE_DIR}/core")
include_directories("${PROJECT_SOURCE_DIR}/core/entities")

add_subdirectory(sdl)
add_subdirectory(core)

set(MESHES
    anti_planet
    goal
    heavy_planet
    light_planet
    medium_planet
    ship
    active_planet
)

set(MENUS
    galaxy
    sector_1
    sector_2
    sector_3
    sector_4
    sector_5
)

set(LEVELS
    level_1_1
    level_1_2
    level_1_3
    level_1_4
    level_2_1
    level_2_2
    level_3_1
    level_3_2
    level_4_1
    level_4_2
    level_5_1
    level_5_2
)

set(BUTTONS
    menu
    restart
    quit
    mute_music
    unmute_music
    mute_efx
    unmute_efx
    heavy_planet
    medium_planet
    light_planet
    anti_planet
    won_level
    lost_level
    counter
)

set(MUSIC
    background
)

if(UNIX)
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/data.txt
        COMMAND echo "$ENV{HOME}/gravity_well" > ${CMAKE_BINARY_DIR}/data.txt
    )
    add_custom_target(data_location ALL DEPENDS ${CMAKE_BINARY_DIR}/data.txt)
    install(FILES ${CMAKE_BINARY_DIR}/data.txt DESTINATION $ENV{HOME}/.gravity_well)

    add_custom_command(
        OUTPUT uninstall_me
        COMMAND rm -f $ENV{HOME}/gravity_well/gravity_well
        COMMAND rm -rf $ENV{HOME}/gravity_well/data
        COMMAND rm -rf $ENV{HOME}/.gravity_well
        COMMAND rm -rf ${CMAKE_SOURCE_DIR}/android/bin
        COMMAND rm -rf ${CMAKE_SOURCE_DIR}/android/gen
        COMMAND rm -rf ${CMAKE_SOURCE_DIR}/android/libs
        COMMAND rm -rf ${CMAKE_SOURCE_DIR}/android/obj
        COMMAND rm -rf ${CMAKE_SOURCE_DIR}/android/assets
    )
    add_custom_target(uninstall DEPENDS uninstall_me)

    foreach(_mesh ${MESHES})
        add_custom_command(
            OUTPUT ${PROJECT_BINARY_DIR}/assets/${_mesh}.mp3
            COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
            COMMAND blender ${PROJECT_SOURCE_DIR}/assets/meshes/${_mesh}.blend -b -P ${PROJECT_SOURCE_DIR}/tools/blender_exporter.py -- ${PROJECT_BINARY_DIR}/assets/${_mesh}.mp3
            DEPENDS ${PROJECT_SOURCE_DIR}/assets/meshes/${_mesh}.blend
            DEPENDS ${PROJECT_SOURCE_DIR}/tools/blender_exporter.py
        )
        add_custom_target(${_mesh} ALL DEPENDS ${PROJECT_BINARY_DIR}/assets/${_mesh}.mp3)
    endforeach()

    foreach(_menu ${MENUS})
        add_custom_command(
            OUTPUT ${PROJECT_BINARY_DIR}/assets/${_menu}.mp3
            COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
            COMMAND blender -b -P ${PROJECT_SOURCE_DIR}/tools/menu_exporter.py -- ${PROJECT_SOURCE_DIR}/assets/levels/${_menu}.lvl ${PROJECT_BINARY_DIR}/assets/${_menu}.mp3
            DEPENDS ${PROJECT_SOURCE_DIR}/assets/levels/${_menu}.lvl
            DEPENDS ${PROJECT_SOURCE_DIR}/tools/menu_exporter.py
        )
        add_custom_target(${_menu} ALL DEPENDS ${PROJECT_BINARY_DIR}/assets/${_menu}.mp3)
    endforeach()

    foreach(_level ${LEVELS})
        add_custom_command(
            OUTPUT ${PROJECT_BINARY_DIR}/assets/${_level}.mp3
            COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
            COMMAND blender -b -P ${PROJECT_SOURCE_DIR}/tools/level_exporter.py -- ${PROJECT_SOURCE_DIR}/assets/levels/${_level}.lvl ${PROJECT_BINARY_DIR}/assets/${_level}.mp3
            DEPENDS ${PROJECT_SOURCE_DIR}/assets/levels/${_level}.lvl
            DEPENDS ${PROJECT_SOURCE_DIR}/tools/level_exporter.py
        )
        add_custom_target(${_level} ALL DEPENDS ${PROJECT_BINARY_DIR}/assets/${_level}.mp3)
    endforeach()

    foreach(_button ${BUTTONS})
        add_custom_command(
            OUTPUT ${PROJECT_BINARY_DIR}/assets/${_button}.button.mp3
            COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
            COMMAND blender -b -P ${PROJECT_SOURCE_DIR}/tools/button_exporter.py -- ${PROJECT_SOURCE_DIR}/assets/buttons/${_button}.button ${PROJECT_BINARY_DIR}/assets/${_button}.button.mp3
            DEPENDS ${PROJECT_SOURCE_DIR}/assets/buttons/${_button}.button
            DEPENDS ${PROJECT_SOURCE_DIR}/tools/button_exporter.py
        )
        add_custom_target(${_button}_button ALL DEPENDS ${PROJECT_BINARY_DIR}/assets/${_button}.button.mp3)
    endforeach()

    foreach(_music ${MUSIC})
        add_custom_command(
            OUTPUT ${PROJECT_BINARY_DIR}/assets/${_music}.ogg
            COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
            COMMAND cp ${PROJECT_SOURCE_DIR}/assets/music/${_music}.ogg ${PROJECT_BINARY_DIR}/assets
            DEPENDS ${PROJECT_SOURCE_DIR}/assets/music/${_music}.ogg
        )
        add_custom_target(${_music} ALL DEPENDS ${PROJECT_BINARY_DIR}/assets/${_music}.ogg)
    endforeach()

    add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/assets/font.mp3
        COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
        COMMAND blender -b -P ${PROJECT_SOURCE_DIR}/tools/font_exporter.py -- ${PROJECT_SOURCE_DIR}/assets/font.txt ${PROJECT_BINARY_DIR}/assets/font.mp3
        DEPENDS ${PROJECT_SOURCE_DIR}/tools/font_exporter.py
        DEPENDS ${PROJECT_SOURCE_DIR}/assets/font.txt
    )
    add_custom_target(font ALL DEPENDS ${PROJECT_BINARY_DIR}/assets/font.mp3)
    install(DIRECTORY ${PROJECT_BINARY_DIR}/assets/ DESTINATION $ENV{HOME}/gravity_well/data)

    add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/assets/tex0.mp3
        COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
        COMMAND cp ${PROJECT_SOURCE_DIR}/assets/textures/tex0.png ${PROJECT_BINARY_DIR}/assets/tex0.mp3
        DEPENDS ${PROJECT_SOURCE_DIR}/assets/textures/tex0.png
    )
    add_custom_target(tex0_png ALL DEPENDS ${PROJECT_BINARY_DIR}/assets/tex0.mp3)

    add_custom_command(
        OUTPUT android-build
        COMMAND cd ${PROJECT_SOURCE_DIR} && rm -rf android/assets && mkdir -p android/assets && cp ${PROJECT_BINARY_DIR}/assets/* android/assets && etc1tool --encodeNoHeader assets/textures/tex0.png && mv assets/textures/tex0.pkm android/assets/tex0.mp3 && rm -f android/assets/*.ogg && rm -f android/assets/*.wav && rm -rf android/res/raw/ && mkdir -p android/res/raw && cp assets/music/*.ogg android/res/raw && cp assets/audio/*.ogg android/res/raw/ && cd android && ndk-build NDK_DEBUG=1 && android update project --path . --name MarbleMachine -s && ant debug && cd bin && adb install -r MarbleMachine-debug.apk && adb shell am start -a android.intent.action.MAIN -n net.leifandersen.mobile.android.marblemachine/.MainActivity
    )
    add_custom_target(android DEPENDS android-build ${MESHES} ${MENUS} ${BUTTONS} ${MUSIC} font)
endif()

if(WIN32)

endif()

set(QT_CREATOR_HACK
    android/jni/os_calls.cpp
    android/jni/jniinterface.cpp
    tools/menu_exporter.py
    tools/level_exporter.py
    tools/blender_exporter.py
    tools/button_exporter.py
)

# Uncomment to edit 'hidden' files, re-comment to compile.
# add_library(jni ${QT_CREATOR_HACK})
