# Install script for directory: C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib

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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/Debug/tag.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/Release/tag.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/MinSizeRel/tag.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/RelWithDebInfo/tag.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/taglib" TYPE FILE FILES
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/tag.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/fileref.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/audioproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/taglib_export.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/../taglib_config.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/taglib.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tstring.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tlist.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tlist.tcc"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tstringlist.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tbytevector.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tbytevectorlist.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tvariant.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tbytevectorstream.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tiostream.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tfilestream.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tmap.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tmap.tcc"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tpicturetype.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tpropertymap.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tdebuglistener.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tversionnumber.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/mpegfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/mpegproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/mpegheader.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/xingheader.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v1/id3v1tag.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v1/id3v1genres.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2extendedheader.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2frame.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2header.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2synchdata.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2footer.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2framefactory.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2tag.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/attachedpictureframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/commentsframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/eventtimingcodesframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/ownershipframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/popularimeterframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/privateframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/relativevolumeframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/synchronizedlyricsframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/textidentificationframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/unknownframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/urllinkframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/chapterframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/tableofcontentsframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/podcastframe.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/oggfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/oggpage.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/oggpageheader.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/xiphcomment.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/vorbis/vorbisfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/vorbis/vorbisproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/flac/oggflacfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/speex/speexfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/speex/speexproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/opus/opusfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/opus/opusproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/flac/flacfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/flac/flacpicture.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/flac/flacproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/flac/flacmetadatablock.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ape/apefile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ape/apeproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ape/apetag.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ape/apefooter.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/ape/apeitem.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpc/mpcfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mpc/mpcproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/wavpack/wavpackfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/wavpack/wavpackproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/trueaudio/trueaudiofile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/trueaudio/trueaudioproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/rifffile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/aiff/aifffile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/aiff/aiffproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/wav/wavfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/wav/wavproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/wav/infotag.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/asf/asffile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/asf/asfproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/asf/asftag.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/asf/asfattribute.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/asf/asfpicture.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4file.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4atom.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4tag.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4item.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4properties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4coverart.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4itemfactory.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mod/modfilebase.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mod/modfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mod/modtag.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/mod/modproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/it/itfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/it/itproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/s3m/s3mfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/s3m/s3mproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/xm/xmfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/xm/xmproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/dsf/dsffile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/dsf/dsfproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/dsdiff/dsdifffile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/dsdiff/dsdiffproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/dsdiff/dsdiffdiintag.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/shorten/shortenfile.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/shorten/shortenproperties.h"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/taglib/shorten/shortentag.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib/taglib-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib/taglib-targets.cmake"
         "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib/taglib-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib/taglib-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib-config.cmake"
    "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib-config-version.cmake"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-release/taglib/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
