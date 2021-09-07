cmake_minimum_required( VERSION 3.0 )

project( Hypothetical-Language-Assembler )

# flags

# include files
include_directories( ./include ./src ./lib/libExampleA/include ./lib/libExampleB/include )

# target
add_executable( main ./src/main.cpp )

# 3rd party lib
add_subdirectory( ./lib/libExampleA )
target_link_libraries( main libExampleA )

# 3rd party lib
add_subdirectory( ./lib/libExampleB )
target_link_libraries( main libExampleB )


add_library(staticalLib STATIC IMPORTED)
set_property(TARGET staticalLib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/staticalLib/libStaticalLib.a)
target_link_libraries( main staticalLib )