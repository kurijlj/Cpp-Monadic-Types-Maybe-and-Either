# ============================================================================
# A CMake build script for the C++ Monadic Types: Maybe and Either
# ============================================================================

# -----------------------------------------------------------------------------
# Define the minimum required version of CMake
# -----------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.14...3.29)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# -----------------------------------------------------------------------------
# Define the project name and version
# -----------------------------------------------------------------------------
project (
  Cpp-Monadic-Types-Maybe-and-Either
  VERSION 0.1
  DESCRIPTION "Implementation of the Maybe/Either monadic types for the C++17"
  HOMEPAGE_URL ""
  LANGUAGES C CXX
  )

# Show which project we are building
message(STATUS "Building '" ${PROJECT_NAME} "' v" ${PROJECT_VERSION})

# Set the C++ standard to C++17 and make it required
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CMake module path
list (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

# Set the build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release)
endif ()

# If build type is Debug set for debugging code to compile
if (CMAKE_BUILD_TYPE MATCHES "Debug")
  message(STATUS "Compile debugging code: 'ON'")
  set(USE_DEBUG ON)
else ()
  message(STATUS "Compile debugging code: 'OFF'")
  set(USE_DEBUG OFF)
endif ()

# Set to build with shared libraries by default
option (BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Set not to build with tests by default
option (BUILD_TESTS "Build with tests" OFF)

# Determine whether the libraries are built as shared or static
if (BUILD_SHARED_LIBS)
  set (LIB_TYPE SHARED)
else ()
  set (LIB_TYPE STATIC)
endif (BUILD_SHARED_LIBS)

# Set the output directory for the executable
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -----------------------------------------------------------------------------
# Check for the presence of required libraries
# -----------------------------------------------------------------------------
message (STATUS "Checking for the required libraries")

# Add the clipp.h library
add_library (clipp INTERFACE)
target_sources (clipp INTERFACE "${PROJECT_SOURCE_DIR}/extern/clipp/clipp.hpp")
target_include_directories (
  clipp
  INTERFACE
  "${PROJECT_SOURCE_DIR}/extern/clipp"
  )

# -----------------------------------------------------------------------------
# Add the source files
# -----------------------------------------------------------------------------
add_subdirectory ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src")

# -----------------------------------------------------------------------------
# Check if we are building with the unit tests
# -----------------------------------------------------------------------------

# Check if the tests are enabled
if (NOT DEFINED BUILD_TESTS)
  option (BUILD_TESTS "Build the tests" OFF)  # Default to OFF
endif ()

# Add the test files directory if the tests are enabled
if (BUILD_TESTS)
  # Enable FetchContent module
  include(FetchContent)

  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )

  FetchContent_MakeAvailable(googletest)
  add_subdirectory ("${PROJECT_SOURCE_DIR}/tests")

endif ()

# End of CMakeLists.txt