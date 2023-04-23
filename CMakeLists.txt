cmake_minimum_required(VERSION 3.14)

project(lostcpp VERSION 0.1)
option(USE_PCH "Use precompiled headers (StdAfx.hpp)" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EMBED_FILES TRUE CACHE BOOL "Embedded files")


include(cmake/embed.cmake)
include(cmake/libraries.cmake)
include(cmake/flags.cmake)

include_directories(src)

file(GLOB_RECURSE LOSTCPP_SOURCES src/*.cpp src/*.hpp)

add_executable(${CMAKE_PROJECT_NAME} ${LOSTCPP_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LOSTCPP_LIBRARIES})

if (USE_PCH)
    target_precompile_headers(${CMAKE_PROJECT_NAME} PUBLIC 
        src/StdAfx.hpp
    )
endif()
