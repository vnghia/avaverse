cmake_minimum_required(VERSION 3.22)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-fcolor-diagnostics)
endif()

# Project
project(
  Avaverse
  VERSION 0.0.1
  LANGUAGES CXX
)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH "${PROJECT_ROOT_DIR}/cmake")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# Prevent building in the source directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
    "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# Ccache
option(ENABLE_CCACHE "Automatically use ccache if available" ON)

if("${ENABLE_CCACHE}")
  find_program(CCACHE_PROGRAM ccache NAMES /usr/bin/ccache)

  if(CCACHE_PROGRAM)
    message(STATUS "ccache found: ${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CC_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  endif()
endif()

# Output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIR}/lib/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIR}/lib/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIR}/bin/${CMAKE_BUILD_TYPE}")

# Eigen
find_package(Eigen3 CONFIG REQUIRED)

# Glfw
find_package(glfw3 REQUIRED)
add_library(glfw::glfw ALIAS glfw)

# CGAL
find_package(CGAL COMPONENTS Core)

# Libigl
option(LIBIGL_USE_STATIC_LIBRARY "Use libIGL as static librarie" ON)
add_compile_definitions(IGL_VIEWER_VIEWER_QUIET)
include(avaverse/external/libigl)
igl_include(png)
igl_include(glfw)

if(CGAL_FOUND)
  igl_include(copyleft/cgal)
  igl_include(copyleft/tetgen)
endif()

target_compile_definitions(igl_glfw INTERFACE IGL_VIEWER_VIEWER_QUIET)

# Cxxopts
include(avaverse/external/cxxopts)

# Build libraries
add_subdirectory(avaverse)

# Build tools
add_subdirectory(tools)
