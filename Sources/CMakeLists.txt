cmake_minimum_required(VERSION 3.13)
project( tydal CXX )

if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug )
endif()

add_library( tydal_core STATIC )
target_include_directories( tydal_core PUBLIC "${PROJECT_SOURCE_DIR}" )
target_compile_options( tydal_core PUBLIC -Wall )

add_subdirectory( GenericParser )
add_subdirectory( OutputTranslator )
add_subdirectory( Tydal )

add_executable( tydal main.cc )
target_link_libraries( tydal PRIVATE tydal_core )
