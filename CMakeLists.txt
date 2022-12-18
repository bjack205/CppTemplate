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
# TIP: You can change options via command line with e.g. "-D MY_OPTION=ON" or cmake-gui (on Linux)

# Handle default build type
# TIP: The build type (Debug, Release, MinSizeSize, RelWithDebInfo) sets the optimization level and other compiler flags
# TIP: If the build type isn't passed in (via e.g. cmake -D CMAKE_BUILD_TYPE=Release) then the default build type isn't
#      well defined, so we set it explicitly
set(${${PROJECT_NAME}_DEFAULT_BUILD_TYPE}  "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)  # Checks if the build type is defined or multi-config generator
  # TIP: here's an example of printing something to the console using CMake
  message(STATUS "No build type specified. Setting CMAKE_BUILD_TYPE to ${ALTRO_DEFAULT_BUILD_TYPE}")

  # TIP: here's an example of setting a "cache" variable that can be modified by user from the command line
  set(CMAKE_BUILD_TYPE ${${PROJECT_NAME}_DEFAULT_BUILD_TYPE} CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Option to enable testing
set(TEST_OPTION "${PROJECT_NAME}_BUILD_TESTS")
option(${TEST_OPTION} "Build tests for ${PROJECT_NAME}" ON)

#############################################
# Dependencies
#############################################

# TIP: Here we add external dependencies. My preferred way is to use the FetchContent module, which clones the
#      dependency into the build directory (usually under _deps/), and adds the CMake directly to the current one,
#      exposing all of the CMake targets to the current project.
#
#      IMHO, this is preferred over the more common approach of "installing" the project into the system root and
#      asking letting CMake to find the compiled binaries, libraries, and header files via find_package, since it
#      doesn't require the user to do anything other than clone the current repository. The version of the external
#      dependencies can then be directly controlled. The downside is that the initial build time goes up significantly
#      since all of the external dependencies need to be built (but this should only happen once).

# Add libfmt
# - This is a nice package for printing things to the console. Much better than using std::cout
list(APPEND CMAKE_MESSAGE_CONTEXT fmt)
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 9.1.0
  )
FetchContent_MakeAvailable(fmt)
list(POP_BACK CMAKE_MESSAGE_CONTEXT)

# Add Eigen
# - A popular template package for linear algebra
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
# TIP: This is a common practice, and enables a bunch of extra compiler checks, and treats compiler warnings as errors
add_compile_options(-Wall -Wextra -pedantic -Werror)

# TIP: This option enables SIMD instructions on most architectures
add_compile_options(-march=native)

# Add a library
# TIP: By default, this builds a static library, unless `BUILD_SHARED_LIBS` is set to true
add_library(foo
  # TIP: Add source files for the library here
  foo.hpp
  foo.cpp)
target_link_libraries(foo
  # TIP: This command links external libraries so they can be called by the source files of this library
  #      It automatically adds the include directories of the external libraries to the include path of the current
  #      library so they can be found
  # TIP: You can link libraries as PRIVATE, PUBLIC, or INTERFACE
  #   - PRIVATE dependencies can only be used by the current source files
  #   - PUBLIC dependencies will be included as a dependency to any library that links against this library.
  #            This is the most robust method, but can unnecessarily increase compilation time if abused.
  #   - INTERFACE dependencies cannot be used by the current source files, but will be added to to a library that links
  #               against this one (for special cases that you typically won't need to worry about)
  # TIP: Use PRIVATE if the library is only used in the implementation (.cpp) file, and PUBLIC otherwise.
  PUBLIC
  Eigen3::Eigen

  PRIVATE
  fmt::fmt)
target_include_directories(foo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add an executable
# TIP: the executable name is the name of the target (main, in this case)
add_executable(main main.cpp)
target_link_libraries(main
  PRIVATE
  foo
  fmt::fmt)

#############################################
# Testing
#############################################
# TIP: If testing is enabled, it adds googletest (pretty much the most common C++ testing framework) and compiles the
#      targets in the `test/` directory
if (TEST_OPTION)
  # Add GoogleTest dependency
  message(STATUS "Building tests for ${PROJECT_NAME}")
  FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850
    )
  FetchContent_MakeAvailable(googletest)

  # Some boilerplate code for testing
  enable_testing()
  include(GoogleTest)
  include(CTest)

  # TIP: Adds the targets defined in the CMakeLists.txt file in the test/ subdirectory
  add_subdirectory(test)
endif()
