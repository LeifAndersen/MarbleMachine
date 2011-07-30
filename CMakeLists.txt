cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "-g -Wall")
project(gravity_well)

Find_Package(SDL REQUIRED)
Find_Package(SDL_mixer REQUIRED)
find_package(OpenGL REQUIRED)

if(NOT SDL_FOUND)
    message ( FATAL_ERROR "SDL not found!")
endif(NOT SDL_FOUND)

link_libraries(
    ${SDL_LIBRARY}
    ${SDLMIXER_LIBRARY}
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
)

set(MENUS
    galaxy
    sector_1
)

add_custom_command(
    OUTPUT uninstall_me
    COMMAND rm -f $ENV{HOME}/gravity_well/gravity_well
    COMMAND rm -rf $ENV{HOME}/gravity_well/data
)
add_custom_target(uninstall DEPENDS uninstall_me)

foreach(_mesh ${MESHES})
    add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/assets/${_mesh}.mp3
        COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
        COMMAND blender ${PROJECT_SOURCE_DIR}/meshes/${_mesh}.blend -b -P ${PROJECT_SOURCE_DIR}/tools/blender_exporter.py -- ${PROJECT_BINARY_DIR}/assets/${_mesh}.mp3
        DEPENDS ${PROJECT_SOURCE_DIR}/meshes/${_mesh}.blend
    )
    add_custom_target(${_mesh} ALL DEPENDS ${PROJECT_BINARY_DIR}/assets/${_mesh}.mp3)
endforeach()

foreach(_menu ${MENUS})
    add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/assets/${_menu}.mp3
        COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
        COMMAND blender -b -P ${PROJECT_SOURCE_DIR}/tools/menu_exporter.py -- ${PROJECT_SOURCE_DIR}/levels/${_menu}.lvl ${PROJECT_BINARY_DIR}/assets/${_menu}.mp3
        DEPENDS ${PROJECT_SOURCE_DIR}/levels/${_menu}.lvl
    )
    add_custom_target(${_menu} ALL DEPENDS ${PROJECT_BINARY_DIR}/assets/${_menu}.mp3)
endforeach()

add_custom_command(
    OUTPUT button
    COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
    COMMAND blender -b -P ${PROJECT_SOURCE_DIR}/tools/button_exporter.py -- ${PROJECT_SOURCE_DIR}/meshes/buttons.txt ${PROJECT_BINARY_DIR}/assets/
    DEPENDS ${PROJECT_SOURCE_DIR}/meshes/buttons.txt
)
add_custom_target(buttons ALL DEPENDS button)

add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/assets/font.mp3
    COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
    COMMAND blender -b -P ${PROJECT_SOURCE_DIR}/tools/font_exporter.py -- ${PROJECT_SOURCE_DIR}/meshes/font.txt ${PROJECT_BINARY_DIR}/assets/font.mp3
)
add_custom_target(font ALL DEPENDS ${PROJECT_BINARY_DIR}/assets/font.mp3)
install(DIRECTORY ${PROJECT_BINARY_DIR}/assets/ DESTINATION $ENV{HOME}/gravity_well/data)

add_custom_command(
    OUTPUT android-build
    COMMAND cd ${PROJECT_SOURCE_DIR} && mkdir -p assets && etc1tool --encodeNoHeader meshes/tex0.png && mv meshes/tex0.pkm assets/tex0.mp3 && cp ${PROJECT_BINARY_DIR}/assets/* assets && cd android && ndk-build NDK_DEBUG=1 && android update project --path . --name MarbleMachine -s && ant debug && cd bin && adb install -r MarbleMachine-debug.apk && adb shell am start -a android.intent.action.MAIN -n net.leifandersen.mobile.android.marblemachine/.MainActivity
)
add_custom_target(android DEPENDS android-build ${MESHES} ${MENUS} buttons font)
