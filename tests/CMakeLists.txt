# =============================================================================
# CMake build script for the 'Cxx_Maybe_Either' unit tests
# =============================================================================

# Print message to console that we are building the source targets
message(STATUS "Going through ./tests")

# =============================================================================
# Set up
# =============================================================================

# Enable testing (this allows us to use the add_test() function)
enable_testing ()

# =============================================================================
# Build source targets
# =============================================================================

# -----------------------------------------------------------------------------
# test_maybe
# -----------------------------------------------------------------------------

# Build the "test_maybe" target
add_executable(test_maybe TestMaybe.cpp)

# Link required libraries for the `test_maybe` target
target_link_libraries(test_maybe PRIVATE
  GTest::gtest_main
  )

# Include the required directories for the `test_maybe` target
target_include_directories (test_maybe PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )

# -----------------------------------------------------------------------------
# test_either
# -----------------------------------------------------------------------------

# Build the "test_either" target
add_executable(test_either TestEither.cpp)

# Link required libraries for the `test_either` target
target_link_libraries(test_either PRIVATE
  GTest::gtest_main
  )

# Include the required directories for the `test_either` target
target_include_directories (test_either PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )

# =============================================================================
# Make tests discoverable
# =============================================================================

# Enable the tests to be discovered by CTest
include(GoogleTest)
gtest_discover_tests(test_maybe)
gtest_discover_tests(test_either)