#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "TagLib::tag" for configuration "MinSizeRel"
set_property(TARGET TagLib::tag APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(TagLib::tag PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/tag.lib"
  )

list(APPEND _cmake_import_check_targets TagLib::tag )
list(APPEND _cmake_import_check_files_for_TagLib::tag "${_IMPORT_PREFIX}/lib/tag.lib" )

# Import target "TagLib::tag_c" for configuration "MinSizeRel"
set_property(TARGET TagLib::tag_c APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(TagLib::tag_c PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/tag_c.lib"
  )

list(APPEND _cmake_import_check_targets TagLib::tag_c )
list(APPEND _cmake_import_check_files_for_TagLib::tag_c "${_IMPORT_PREFIX}/lib/tag_c.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
