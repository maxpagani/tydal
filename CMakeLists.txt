cmake_minimum_required(VERSION 3.13)
project(Tydal CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include(CTest)

add_subdirectory(Sources)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
