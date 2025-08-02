cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME VoxEngine)

project(${PROJECT_NAME} C)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(
    ${GLFW_INCLUDE_DIRS}
    extern/include
)

set(SOURCES
  src/main.c
  extern/src/glad.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    ${GLFW_LIBRARIES}
    dl  
    m   
    pthread  
    X11  
)
