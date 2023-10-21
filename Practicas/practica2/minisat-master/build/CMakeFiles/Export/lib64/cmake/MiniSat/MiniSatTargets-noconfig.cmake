#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MiniSat::libminisat" for configuration ""
set_property(TARGET MiniSat::libminisat APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MiniSat::libminisat PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib64/libminisat.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MiniSat::libminisat )
list(APPEND _IMPORT_CHECK_FILES_FOR_MiniSat::libminisat "${_IMPORT_PREFIX}/lib64/libminisat.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
