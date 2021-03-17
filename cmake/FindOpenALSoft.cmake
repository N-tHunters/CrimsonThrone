# - Try to find OpenAL-soft (custom)
# Once done, this will define
#
# OPENALSOFT_FOUND - system has OpenAL-soft
# OPENALSOFT_INCLUDE_DIR - the OpenAL-soft include directories
# OPENALSOFT_LIBRARIES - link these to use OpenAL-soft
if(UNIX)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
elseif(WIN32)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
endif()


FIND_PATH( OPENALSOFT_INCLUDE_DIR AL/al.h
  /usr/include
  /usr/local/include
  /opt/local/include
  "${CMAKE_SOURCE_DIR}/include"
  )

FIND_LIBRARY( OPENALSOFT_LIBRARY NAMES OpenAL32 libopenal.so
  PATHS
  /usr/lib64
  /usr/lib
  /usr/local/lib
  /opt/local/lib
  /usr/lib/x86_64-linux-gnu
  "${CMAKE_SOURCE_DIR}/lib"
  )

IF(OPENALSOFT_INCLUDE_DIR AND OPENALSOFT_LIBRARY)
  SET( OPENALSOFT_FOUND TRUE )
ENDIF(OPENALSOFT_INCLUDE_DIR AND OPENALSOFT_LIBRARY)
IF(OPENALSOFT_FOUND)
  IF(NOT OPENALSOFT_FIND_QUIETLY)
    MESSAGE(STATUS "Found OpenAL-soft: ${OPENALSOFT_LIBRARY}")
  ENDIF(NOT OPENALSOFT_FIND_QUIETLY)
ELSE(OPENALSOFT_FOUND)
  IF(OPENALSOFT_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find OpenAL32")
  ENDIF(OPENALSOFT_FIND_REQUIRED)
ENDIF(OPENALSOFT_FOUND)
