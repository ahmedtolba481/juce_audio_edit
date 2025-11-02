if (NOT EXISTS "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-debug/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-debug/install_manifest.txt\"")
endif()

file(READ "C:/Users/eyadd/Documents/CPP/CS 213/Assignment-2/Ahmed/juce_audio_edit/Source/taglib-2.1.1/build-debug/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    execute_process(
      COMMAND C:/Program Files/CMake/bin/cmake.exe -E remove "$ENV{DESTDIR}${file}"
      OUTPUT_VARIABLE rm_out
      RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
      message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif ()
  else ()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif ()
endforeach()
