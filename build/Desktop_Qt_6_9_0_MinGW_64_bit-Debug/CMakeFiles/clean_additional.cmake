# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Tweaker_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Tweaker_autogen.dir\\ParseCache.txt"
  "Tweaker_autogen"
  )
endif()
