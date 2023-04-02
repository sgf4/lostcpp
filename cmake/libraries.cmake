set(CMAKE_BUILD_TYPE_OLD "${CMAKE_BUILD_TYPE}")
set(CMAKE_BUILD_TYPE "Release")
include(cmake/glfw.cmake)
include(cmake/stduuid.cmake)
include(cmake/assimp.cmake)
include(cmake/glm.cmake)
set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE_OLD}")

set(LOSTCPP_LIBRARIES glm glfw stduuid assimp)