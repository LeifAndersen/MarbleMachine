cmake_minimum_required(VERSION 2.6)
project(gravity_well)

file(GLOB SDL_PORT "sdl/*.cpp")
file(GLOB CORE "core/*.cpp")
file(GLOB CORE_ENTITIES "core/entities/*.cpp")
file(GLOB MESHES "meshes/*.blend")
file(GLOB LEVELS "levels/*.lvl")

include_directories("${PROJECT_SOURCE_DIR}/sdl")
include_directories("${PROJECT_SOURCE_DIR}/core")
include_directories("${PROJECT_SOURCE_DIR}/core/entities")

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
)

set(CMAKE_CXX_FLAGS "-g -Wall")

set(SOURCES ${SDL_PORT} ${CORE} ${CORE_ENTITIES})

add_executable(gravity_well WIN32 MACOSX_BUNDLE ${SOURCES})

install(TARGETS gravity_well DESTINATION $ENV{HOME}/gravity_well)
#install(FILES ${PROJECT_SOURCE_DIR}/assets/* DESTINATION include)
