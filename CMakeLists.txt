cmake_minimum_required(VERSION 3.30)

set(PROJECT_NAME VoxEngine)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${PROJECT_NAME} 
        VERSION 0.1
        DESCRIPTION "Voxel rendering engine made in OpenGL"
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ENABLE_SANITIZERS "Enable runtime sanitizers" OFF)

if(ENABLE_SANITIZERS)
    message(STATUS "Sanitizers enabled")
    set(SANITIZER_FLAGS "-fsanitize=address,undefined -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZER_FLAGS}")
endif()

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(assimp REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/extern/glad
    ${CMAKE_SOURCE_DIR}/extern/KHR
    ${CMAKE_SOURCE_DIR}/extern/glm-1.0.1
    ${CMAKE_SOURCE_DIR}/extern
)

add_library(glad STATIC extern/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/extern/glad ${CMAKE_SOURCE_DIR}/extern/KHR)

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${CMAKE_SOURCE_DIR}/extern/glm-1.0.1)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_SOURCE_DIR}/extern)

add_executable(${PROJECT_NAME} 
  ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  glad
  glm
  stb
  ${OPENGL_LIBRARIES}
  ${GLFW_LIBRARIES}
  assimp::assimp
)
