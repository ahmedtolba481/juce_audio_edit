# Install script for directory: E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/bindings/c

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/taglib")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-release/bindings/c/Debug/tag_c.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-release/bindings/c/Release/tag_c.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-release/bindings/c/MinSizeRel/tag_c.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-release/bindings/c/RelWithDebInfo/tag_c.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/taglib" TYPE FILE FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/bindings/c/tag_c.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE RENAME "taglib_c.pc" FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-release/bindings/c/taglib_c.pc")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-release/bindings/c/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
