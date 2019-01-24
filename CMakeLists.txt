cmake_minimum_required( VERSION 3.12 )
project( JoinJson )

add_subdirectory( CppAidKit )
include( CppAidKit/cmake/all_options.cmake )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

file( COPY Common.json DESTINATION ${CMAKE_BINARY_DIR} )
file( COPY Framework.json DESTINATION ${CMAKE_BINARY_DIR} )
file( COPY Blocks.json DESTINATION ${CMAKE_BINARY_DIR} )

###############################################################################
# Setup Qt

find_package( Qt5 QUIET COMPONENTS Core )
if ( Qt5Core_FOUND )
	add_executable( qjoinjson src/joinjson_qt.cpp )
	target_link_libraries( qjoinjson AidKit Qt5::Core )
endif()

################################################################################
## Setup Boost

find_package( Boost QUIET )
if ( Boost_FOUND )
	add_executable( bjoinjson src/joinjson_boost.cpp )
	target_link_libraries( bjoinjson AidKit Boost::boost )
endif()