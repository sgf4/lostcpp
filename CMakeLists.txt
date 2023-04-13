cmake_minimum_required(VERSION 3.14)

project(lostcpp VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(cmake/embed.cmake)
include(cmake/libraries.cmake)


include(cmake/flags.cmake)

include_directories(src)

file(GLOB_RECURSE LOSTCPP_SOURCES src/*.cpp src/*.hpp build/embeds.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${LOSTCPP_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LOSTCPP_LIBRARIES})
target_precompile_headers(${CMAKE_PROJECT_NAME} PUBLIC 
    src/StdAfx.hpp
)