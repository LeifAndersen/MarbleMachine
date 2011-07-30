set(SOURCES sdl_main.cpp os_calls.cpp)

add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/assets/tex0.mp3
    COMMAND mkdir -p ${PROJECT_BINARY_DIR}/assets
    COMMAND convert ${PROJECT_SOURCE_DIR}/meshes/tex0.png ${PROJECT_BINARY_DIR}/assets/tex0.bmp
    COMMAND mv ${PROJECT_BINARY_DIR}/assets/tex0.bmp ${PROJECT_BINARY_DIR}/assets/tex0.mp3
    DEPENDS ${PROJECT_SOURCE_DIR}/meshes/tex0.png
)

add_executable(gravity_well WIN32 MACOSX_BUNDLE ${SOURCES} ${PROJECT_BINARY_DIR}/assets/tex0.mp3)
install(TARGETS gravity_well DESTINATION $ENV{HOME}/gravity_well)

