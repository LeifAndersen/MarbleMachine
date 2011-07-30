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
anti_planet.blend
goal.blend
heavy_planet.blend
light_planet.blend
medium_planet.blend
ship.blend
)
