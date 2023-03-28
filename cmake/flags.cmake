
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Werror -Wno-format-security")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffunction-sections -fdata-sections -fno-rtti -fvisibility=hidden -DNDEBUG")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_EXE_LINKER_FLAGS "-s -flto -Wl,--gc-sections -Wl,--strip-all")
endif()


if (UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
elseif(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -fstack-protector")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)