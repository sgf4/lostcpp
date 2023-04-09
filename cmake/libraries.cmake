set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(CMAKE_BUILD_TYPE_OLD "${CMAKE_BUILD_TYPE}")
set(CMAKE_BUILD_TYPE "Release")

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

add_subdirectory(stduuid)

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
add_subdirectory(assimp)

set(ODE_WITH_DEMOS OFF CACHE BOOL "" FORCE)
set(ODE_WITH_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(ODE)

add_subdirectory(glm)


set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE_OLD}")

set(LOSTCPP_LIBRARIES glm glfw stduuid assimp ODE)