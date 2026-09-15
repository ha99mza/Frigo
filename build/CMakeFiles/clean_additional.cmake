# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  [[CMakeFiles\FrigoHMI_autogen.dir\AutogenUsed.txt]]
  [[CMakeFiles\FrigoHMI_autogen.dir\ParseCache.txt]]
  "FrigoHMI_autogen"
  )
endif()
