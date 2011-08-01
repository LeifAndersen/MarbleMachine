add_subdirectory(entities)

link_libraries(entities)

set(SOURCES
    data_importer.cpp
    data_importer.h
    game_state.cpp
    game_state.h
    glview.cpp
    glview.h
    include_opengl.h
    input_converter.cpp
    input_converter.h
    main.cpp
    main.h
    matrix.cpp
    matrix.h
    os_calls.h
    physics.cpp
    physics.h
    point.cpp
    point.h
)

add_library(core ${SOURCES})
