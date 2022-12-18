cmake_minimum_required(VERSION 3.23)

# Change the project name here
# TIP: You can access this name with PROJECT_NAME
project(CppTemplate VERSION 0.1.0)

# Add message context for CMake Output
# TIP: You can turn on by passing the --log-context argument to cmake
list(APPEND CMAKE_MESSAGE_CONTEXT CppTemplate)

# Include useful modules
# TIP: Modules are built-in CMake "libraries" that contain useful CMake commands
include(FetchContent)

#############################################
# Options
#############################################

# TIP: This section adds compile-time options to the build
# TIP: You can change options via command line with e.g. "-D MY_OPTION=ON"

# Handle default build type
set(${${PROJECT_NAME}_DEFAULT_BUILD_TYPE}  "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type specified. Setting CMAKE_BUILD_TYPE to ${ALTRO_DEFAULT_BUILD_TYPE}")
  set(CMAKE_BUILD_TYPE ${${PROJECT_NAME}_DEFAULT_BUILD_TYPE} CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Enable testing
set(TEST_OPTION "${PROJECT_NAME}_BUILD_TESTS")
option(TEST_OPTION "Build tests for ${PROJECT_NAME}" ON)

#############################################
# Dependencies
#############################################

# Add libfmt
list(APPEND CMAKE_MESSAGE_CONTEXT fmt)
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 9.1.0
  )
FetchContent_MakeAvailable(fmt)
list(POP_BACK CMAKE_MESSAGE_CONTEXT)

# Add Eigen
list(APPEND CMAKE_MESSAGE_CONTEXT eigen)
set(EIGEN_BUILD_DOC OFF CACHE BOOL "Enable creation of Eigen documentation." FORCE)
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "Enable creation of Eigen tests." FORCE)
FetchContent_Declare(eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
  )
FetchContent_MakeAvailable(eigen)
list(POP_BACK CMAKE_MESSAGE_CONTEXT)

#############################################
# Build
#############################################

# Add compile options
add_compile_options(-Wall -Wextra -pedantic -Werror -march=native)

# Add a library
# TIP: Add all the source files
add_library(foo
  foo.hpp
  foo.cpp)
target_link_libraries(foo
  PRIVATE
  Eigen3::Eigen
  fmt::fmt)
target_include_directories(foo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp)
target_link_libraries(main
  PRIVATE
  foo
  fmt::fmt)

#############################################
# Testing
#############################################
if (TEST_OPTION)
  message(STATUS "Building tests for ${PROJECT_NAME}")
  FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850
    )
  FetchContent_MakeAvailable(googletest)
  enable_testing()
  include(GoogleTest)
  include(CTest)
  add_subdirectory(test)
endif()
