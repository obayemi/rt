# Try to find the JsonCPP library
#
# This module defines the following variables:
# 
# JSONCPP_FOUND            - If JsonCPP was found
# JSONCPP_INCLUDE_DIR      - The include directory of JsonCPP
# JSONCPP_LIBRARY          - Link against this variable
# JSONCPP_LIBRARY_DEBUG    - Contains the debug library if found. Otherwise, contains the release.
# JSONCPP_LIBRARY_RELEASE  - Contains the release library if found. Otherwise, contains the debug.
# 
# This module will use the following variables:
# 
# JSONCPP_ROOT - This will be used to find JsonCPP
#

# Defines potential paths for finding JsonCPP
SET(JSONCPP_FIND_PATHS
  ${JSONCPP_ROOT}
  "C:/Program Files (x86)/jsoncpp"
  "C:/Program Files/jsoncpp"
  $ENV{JSONCPP_ROOT}
  /usr/local/
  /usr/
  /sw
  /opt/local/
  /opt/csw/
  /opt/
)

if (NOT JSONCPP_FIND_QUIETLY)
  message(STATUS "Looking for JsonCPP...")
endif ()

# Look for include folder
find_path(JSONCPP_INCLUDE_DIR NAMES json/json.h jsoncpp/json/json.h
  HINTS
    ${JSONCPP_FIND_PATHS}
  PATH_SUFFIXES include)

# Look for debug library
find_library(JSONCPP_LIBRARY_DEBUG
  NAMES         jsoncpp_d
  PATH_SUFFIXES lib64 lib
  PATHS         ${JSONCPP_FIND_PATHS})

# Look for release library
find_library(JSONCPP_LIBRARY_RELEASE
  NAMES         jsoncpp
  PATH_SUFFIXES lib64 lib
  PATHS         ${JSONCPP_FIND_PATHS})

# If at least one library was found
if (JSONCPP_LIBRARY_DEBUG OR JSONCPP_LIBRARY_RELEASE)

  # Mark as found
  SET(JSONCPP_FOUND TRUE)

  if (JSONCPP_LIBRARY_DEBUG AND JSONCPP_LIBRARY_RELEASE)
    # Both libraries were found
    SET(JSONCPP_LIBRARY
      debug     ${JSONCPP_LIBRARY_DEBUG}
      optimized ${JSONCPP_LIBRARY_RELEASE})

  elseif(JSONCPP_LIBRARY_DEBUG)
    # Only debug version was found
    SET(JSONCPP_LIBRARY ${JSONCPP_LIBRARY_DEBUG})
    SET(JSONCPP_LIBRARY_RELEASE ${JSONCPP_LIBRARY_DEBUG})

  elseif(JSONCPP_LIBRARY_RELEASE)
    # Only release version was found
    SET(JSONCPP_LIBRARY ${JSONCPP_LIBRARY_RELEASE})
    SET(JSONCPP_LIBRARY_DEBUG ${JSONCPP_LIBRARY_RELEASE})
  endif()
else()
  # JsonCPP was not found
  SET(JSONCPP_FOUND FALSE)
endif()

# Don't show variables to user
mark_as_advanced(
  JSONCPP_INCLUDE_DIR
  JSONCPP_LIBRARY
  JSONCPP_LIBRARY_RELEASE
  JSONCPP_LIBRARY_DEBUG
)

if (JSONCPP_FOUND)
  message(STATUS "-- Found JsonCPP : ${JSONCPP_LIBRARY}")
else()
  if(JSONCPP_FIND_REQUIRED)
    # Fatal error
    message(FATAL_ERROR "Could NOT find JsonCPP")
  elseif(NOT JSONCPP_FIND_QUIETLY)
    # Error, but continue
    message("Could NOT find JsonCPP")
  endif()
endif()
