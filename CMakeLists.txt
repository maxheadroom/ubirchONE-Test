#=============================================================================
# ubirch #1 cmake file
#=============================================================================
cmake_minimum_required(VERSION 3.3)

# include the local configuration
include(config.cmake)

# the toolchain file (see https://github.com/ubirch/avr-arduino-cmake)
set(CMAKE_TOOLCHAIN_FILE cmake/avr-arduino-toolchain.cmake)

# project name and code types we use
project(ubirchONE_Test C CXX ASM)

# adding our libraries, sources
add_libraries(lib)
add_sources(src)

# add the sketches directory (contains sketch directories and a "libraries" dir where dependent
# libs are extracted
add_sketches(sketches)
