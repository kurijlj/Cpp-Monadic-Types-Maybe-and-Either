# =============================================================================
# CMake build script for the 'Cxx_Maybe_Either' targets
# =============================================================================

# Print message to console that we are building the source targets
message(STATUS "Going through ./src")

# =============================================================================
# Build source targets
# =============================================================================

# -----------------------------------------------------------------------------
# maybe_either_demo
# -----------------------------------------------------------------------------

# Show message that we are building the `maybe_either_demo' target
message (STATUS "Configuring the `maybe_either_demo' target")

# Set the source files for the `maybe_either_demo' target
add_executable (maybe_either_demo
  MaybeEitherDemo.cpp
  MaybeEitherDemoImplementation.cpp
  ExpensiveToCopy.cpp
  )

# Link required libraries for the `maybe_either_demo` target
target_link_libraries(maybe_either_demo PRIVATE
  clipp
  )

# Include the required directories for the `maybe_either_demo` target
target_include_directories (maybe_either_demo PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/extern
  )

# End of CMakeLists.txt