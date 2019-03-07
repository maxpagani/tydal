set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_BUILD_TYPE DEBUG)
project( tydal )

add_executable( tydal main.cc )

add_subdirectory( GenericParser )
add_subdirectory( OutputTranslator )
add_subdirectory( Tydal )

include_directories( "${PROJECT_SOURCE_DIR}" )

set( CMAKE_CXX_FLAGS_DEBUG "-Wall" )
set( CMAKE_CXX_FLAGS_RELEASE "-Wall" )

