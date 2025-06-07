# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ProyectoProgramacion3v2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ProyectoProgramacion3v2_autogen.dir\\ParseCache.txt"
  "ProyectoProgramacion3v2_autogen"
  )
endif()
