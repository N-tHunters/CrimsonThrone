cmake_minimum_required(VERSION 3.10)
project(CrimsonThrone)

# Add .lib files
link_directories({$CMAKE_SOURCE_DIR}/lib)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/src/*.c
  ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
  ${CMAKE_SOURCE_DIR}/src/*.h
  ${CMAKE_SOURCE_DIR}/src/*.hpp)

# Configure header file
configure_file(src/helpers/config.h.in src/helpers/config.h)
include_directories(${CMAKE_BINARY_DIR}/src)

# Define the executable

add_executable(${PROJECT_NAME}
  main.cpp
  ${HEADER_FILES}
  ${SOURCE_FILES})


# Include directories
include_directories(
  "${CMAKE_SOURCE_DIR}/src"
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_SOURCE_DIR}/thirdparty"
  )

# Find required packages and libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# OpenGL
find_package(OpenGL REQUIRED)

# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "GLFW3 included at ${GLFW3_INCLUDE_DIR}")
message(STATUS "GLFW3 library found at ${GLFW3_LIBRARY}")

# GLEW
find_package(GLEW)
if(NOT GLEW_FOUND)
  message(STATUS "GLEW is not found by default script, setting it manually (works for Windows only)")
  set(GLEW_LIBRARY "${CMAKE_SOURCE_DIR}/lib/glew32.lib")
endif()

message(STATUS "GLEW library found at ${GLEW_LIBRARY}")

# Assimp
find_package(ASSIMP REQUIRED)
message(STATUS "ASSIMP included at ${GLFW3_INCLUDE_DIR}")

# Freetype
find_package(Freetype)
if(NOT FREETYPE_FOUND)
  message(STATUS "Freetype is not found by default script, setting it manually (works for Windows only)")
  set(FREETYPE_LIBRARY "${CMAKE_SOURCE_DIR}/lib/freetype.lib")
endif()

message(STATUS "Freetype library found at ${FREETYPE_LIBRARY}")


# STB_IMAGE
add_library(STB_IMAGE "thirdparty/stb_image.cpp")
add_library(GLAD "thirdparty/glad.c")

# OpenAL
find_package(OpenALSoft REQUIRED)
message(STATUS "OpenAL-soft included at ${OPENALSOFT_INCLUDE_DIR}")
message(STATUS "OpenAL-soft library found at ${OPENALSOFT_LIBRARY}")


set(LIBS
  ${GLFW3_LIBRARY}
  ${OPENGL_LIBRARY}
  ${GLEW_LIBRARY}
  ${ASSIMP_LIBRARIES}
  ${OPENALSOFT_LIBRARY}
  ${FREETYPE_LIBRARY}
  STB_IMAGE
  GLAD
  )


target_link_libraries(${PROJECT_NAME} ${LIBS})


# Set variables that are needed
set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -Wall -O3 -s")

# Copy dlls
if(WIN32)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/dlls"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

