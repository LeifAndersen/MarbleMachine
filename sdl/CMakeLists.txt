set(SOURCES sdl_main.cpp os_calls.cpp)
add_executable(gravity_well WIN32 MACOSX_BUNDLE ${SOURCES})

install(TARGETS gravity_well DESTINATION $ENV{HOME}/gravity_well)
#install(FILES ${PROJECT_SOURCE_DIR}/assets/* DESTINATION include)
