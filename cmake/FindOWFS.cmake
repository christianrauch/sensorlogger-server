# - Find OWFS
# Find the native OWFS includes and library
# This module defines
#  OWFS_INCLUDE_DIR, where to find owcapi.h, etc.
#  OWFS_LIBRARIES, the libraries needed to use .
#  OWFS_FOUND, If false, do not try to use owcapi etc.


FIND_PATH(OWFS_INCLUDE_DIR owcapi.h)

FIND_LIBRARY(OWFS_LIBRARIES NAMES owcapi)

IF (OWFS_LIBRARIES AND OWFS_INCLUDE_DIR)
  SET(OWFS_FOUND "YES")
ELSE (OWFS_LIBRARIES AND OWFS_INCLUDE_DIR)
  SET(OWFS_FOUND "NO")
ENDIF (OWFS_LIBRARIES AND OWFS_INCLUDE_DIR)

IF (OWFS_FOUND)
   IF (NOT OWFS_FIND_QUIETLY)
      MESSAGE(STATUS "Found OWFS: ${OWFS_LIBRARIES}")
   ENDIF (NOT OWFS_FIND_QUIETLY)
ELSE (OWFS_FOUND)
   IF (OWFS_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find OWFS library, please configure OWFS_LIBRARIES and OWFS_INCLUDE_DIR")
   ENDIF (OWFS_FIND_REQUIRED)
ENDIF (OWFS_FOUND)

MARK_AS_ADVANCED(OWFS_LIBRARIES OWFS_INCLUDE_DIR)
