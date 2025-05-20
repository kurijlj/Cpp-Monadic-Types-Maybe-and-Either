# =============================================================================
# CMake build script for the 'CxxODBSQLiteFramework' include files
# =============================================================================

# Print message to console that we are processing './include' dir
message(STATUS "Going through ./include")

# =============================================================================
# Configure include files
# =============================================================================

message (STATUS "Configuring 'MaybeEitherCommon.h'")
configure_file(
  ${PROJECT_SOURCE_DIR}/include/MaybeEitherCommon.h.in
  ${PROJECT_SOURCE_DIR}/include/MaybeEitherCommon.h
  @ONLY
  )

# End of CMakeLists.txt