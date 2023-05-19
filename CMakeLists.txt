# Copyright (C) 2023 sgf4
#
# This file is part of lostcpp.
#
# lostcpp is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# lostcpp is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with lostcpp.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.14)

project(lostcpp VERSION 0.1)
option(USE_PCH "Use precompiled headers (StdAfx.hpp)" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)


# -ffunction-sections -fdata-sections
#set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffunction-sections -fdata-sections -fvisibility=hidden -fno-rtti")


message("Embedding files...")

find_package(Python3 REQUIRED)

set(EMBED_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/tools/embed.py")
file(GLOB_RECURSE EMBED_FILES res/*)

execute_process(
  COMMAND ${Python3_EXECUTABLE} ${EMBED_SCRIPT} ${EMBED_FILES}
)

add_subdirectory(marble)
include_directories(src)

file(GLOB_RECURSE LOSTCPP_SOURCES src/*.cpp src/*.hpp)

add_executable(lostcpp ${LOSTCPP_SOURCES})
target_link_libraries(lostcpp PUBLIC marble)

if (USE_PCH)
  target_precompile_headers(lostcpp PRIVATE
    src/stdafx.hpp
  )
endif()


set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address")
# set (CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffunction-sections -fdata-sections -fvisibility=hidden")
# set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffunction-sections -fdata-sections -fvisibility=hidden")
if (WIN32)
  set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} -s -static")
endif()
