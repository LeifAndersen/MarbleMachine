cmake_minimum_required(VERSION 2.6)
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

set(CMAKE_CXX_FLAGS "-g -Wall")

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

foreach(_mesh ${MESHES})
    add_custom_command(
        OUTPUT ${_mesh}.mp3
        COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
        COMMAND blender ${PROJECT_SOURCE_DIR}/meshes/${_mesh}.blend -b -P ${PROJECT_SOURCE_DIR}/tools/blender_exporter.py -- ${PROJECT_BINARY_DIR}/assets/${_mesh}.mp3
        DEPENDS ${PROJECT_SOURCE_DIR}/meshes/${_mesh}.blend
    )
    add_custom_target(${_mesh} ALL DEPENDS ${_mesh}.mp3)
endforeach()
