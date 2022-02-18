# find Flir SDK lib
#
# exports:
#
#   Flir_FOUND
#   Flir_INCLUDE_DIRS
#   Flir_LIBRARIES
#

include(FindPackageHandleStandardArgs)

get_filename_component( Flir_ROOT "/opt/spinnaker" ABSOLUTE )

# Include dir
find_path(Flir_INCLUDE_DIR 
    NAMES include/Spinnaker.h
    PATHS ${Flir_ROOT})

# The library itself
find_library(Flir_LIBRARY
  NAMES libSpinnaker.so
  PATHS ${Flir_ROOT}/lib/
)

# Response handler when find-package is called
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Flir DEFAULT_MSG Flir_LIBRARY Flir_INCLUDE_DIR)

# Set the cmake variable
set(Flir_LIBRARIES ${Flir_LIBRARY})
set(Flir_INCLUDE_DIRS ${Flir_INCLUDE_DIR} ${Flir_ROOT}/include)
set(Flir_FOUND yes)