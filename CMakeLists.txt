cmake_minimum_required( VERSION 3.0 )

project( Hypothetical-Language-Assembler VERSION 0.1)

# flags


# variables

set( argsLib "lib/args/include")
set( simulatorLib "lib/simulator/include")
set( assemblerLib "lib/assembler/include")

# include files
include_directories( include ${assemblerLib} ${argsLib} ${simulatorLib} )
include(CTest)
enable_testing()
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libbin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libbin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}./../bin)


# target
add_executable( assemblerMain ./src/main.cpp ./src/utils.cpp ./src/stringUtils.cpp )

# 3rd party lib
add_subdirectory( ./lib/args )
target_link_libraries( assemblerMain args )

# 3rd party lib
add_subdirectory( ./lib/simulator )
target_link_libraries( assemblerMain simulator )

# 3rd party lib
add_subdirectory( ./lib/assembler )
target_link_libraries( assemblerMain assembler )

# # Statical libs
# add_library (utils STATIC src/utils.cpp)