
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Werror -Wno-format-security")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffunction-sections -fdata-sections -fno-rtti -fvisibility=hidden -DNDEBUG")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections -Wl,--strip-all")
endif()


if(UNIX)
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined")
elseif(WIN32)
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -s -static -fstack-protector -mwindows")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
