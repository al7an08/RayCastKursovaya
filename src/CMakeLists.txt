cmake_minimum_required (VERSION 3.2)

project(RayCastKursovaya)

find_package(SFML 2.4 COMPONENTS audio graphics window system REQUIRED)

set(SOURCES
    main.cpp
    Header.h
    ConvertSketch.cpp
    ConvertSketch.h
    DegToRad.cpp
    DegToRad.h
    GetDegrees.cpp
    GetDegrees.h
    MapCollision.cpp
    MapCollision.h
    Player.cpp
    Player.h
    RadToDeg.cpp
    RadToDeg.h
)

add_executable(RayCast ${SOURCES})

target_link_libraries(RayCast sfml-audio sfml-graphics sfml-window sfml-system)

include_directories($(CMAKE_SOURCE_DIR)/SFML/include)

set_target_properties(RayCast PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})