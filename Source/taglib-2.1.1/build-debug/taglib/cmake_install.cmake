# Install script for directory: E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib

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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/Debug/tag.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/Release/tag.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/MinSizeRel/tag.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/RelWithDebInfo/tag.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/taglib" TYPE FILE FILES
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/tag.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/fileref.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/audioproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/taglib_export.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/../taglib_config.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/taglib.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tstring.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tlist.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tlist.tcc"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tstringlist.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tbytevector.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tbytevectorlist.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tvariant.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tbytevectorstream.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tiostream.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tfilestream.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tmap.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tmap.tcc"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tpicturetype.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tpropertymap.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tdebuglistener.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/toolkit/tversionnumber.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/mpegfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/mpegproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/mpegheader.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/xingheader.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v1/id3v1tag.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v1/id3v1genres.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2extendedheader.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2frame.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2header.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2synchdata.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2footer.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2framefactory.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/id3v2tag.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/attachedpictureframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/commentsframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/eventtimingcodesframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/ownershipframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/popularimeterframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/privateframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/relativevolumeframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/synchronizedlyricsframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/textidentificationframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/unknownframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/urllinkframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/chapterframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/tableofcontentsframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpeg/id3v2/frames/podcastframe.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/oggfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/oggpage.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/oggpageheader.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/xiphcomment.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/vorbis/vorbisfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/vorbis/vorbisproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/flac/oggflacfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/speex/speexfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/speex/speexproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/opus/opusfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ogg/opus/opusproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/flac/flacfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/flac/flacpicture.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/flac/flacproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/flac/flacmetadatablock.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ape/apefile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ape/apeproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ape/apetag.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ape/apefooter.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/ape/apeitem.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpc/mpcfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mpc/mpcproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/wavpack/wavpackfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/wavpack/wavpackproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/trueaudio/trueaudiofile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/trueaudio/trueaudioproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/rifffile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/aiff/aifffile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/aiff/aiffproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/wav/wavfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/wav/wavproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/riff/wav/infotag.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/asf/asffile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/asf/asfproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/asf/asftag.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/asf/asfattribute.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/asf/asfpicture.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4file.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4atom.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4tag.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4item.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4properties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4coverart.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mp4/mp4itemfactory.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mod/modfilebase.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mod/modfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mod/modtag.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/mod/modproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/it/itfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/it/itproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/s3m/s3mfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/s3m/s3mproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/xm/xmfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/xm/xmproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/dsf/dsffile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/dsf/dsfproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/dsdiff/dsdifffile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/dsdiff/dsdiffproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/dsdiff/dsdiffdiintag.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/shorten/shortenfile.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/shorten/shortenproperties.h"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/taglib/shorten/shortentag.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib/taglib-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib/taglib-targets.cmake"
         "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets.cmake")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib-config.cmake"
    "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib-config-version.cmake"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "E:/Tarek/Collage/Second Year/First Semester/OOP/Assignments/Assignment 2 AhmedVerison/juce_audio_edit/Source/taglib-2.1.1/build-debug/taglib/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
