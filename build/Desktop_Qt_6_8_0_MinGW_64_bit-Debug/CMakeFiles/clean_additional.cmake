# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Shop_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Shop_autogen.dir\\ParseCache.txt"
  "Shop_autogen"
  )
endif()
