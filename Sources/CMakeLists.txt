cmake_minimum_required(VERSION 3.13)
project( tydal CXX )

if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug )
endif()

add_executable( tydal main.cc )
target_include_directories( tydal PRIVATE "${PROJECT_SOURCE_DIR}" )
target_compile_options( tydal PRIVATE -Wall )

add_subdirectory( GenericParser )
add_subdirectory( OutputTranslator )
add_subdirectory( Tydal )

include( CTest )

#add_test( )
