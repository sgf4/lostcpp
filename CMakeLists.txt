cmake_minimum_required(VERSION 3.14)

project(lostcpp VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/flags.cmake)
include(cmake/embed.cmake)
include(cmake/glfw.cmake)
include(cmake/stduuid.cmake)
include(cmake/glm.cmake)

include_directories(src)

file(GLOB_RECURSE LOSTCPP_SOURCES src/*.cpp build/embeds.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${LOSTCPP_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} glm glfw stduuid)