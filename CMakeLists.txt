set(VCPKG_TARGET_TRIPLET x86-windows-static CACHE STRING "target triplet" FORCE)
set(CMAKE_TOOLCHAIN_FILE vcpkg/scripts/buildsystems/vcpkg.cmake CACHE FILEPATH "Path to vcpkg submodule" FORCE)

cmake_minimum_required(VERSION 3.19)
project(CompileCommands)

include(CMakePrintHelpers)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(CppAidKit)
include(CppAidKit/cmake/AidKit.cmake)

#file( COPY Common.json DESTINATION ${CMAKE_BINARY_DIR} )
#file( COPY Framework.json DESTINATION ${CMAKE_BINARY_DIR} )
#file( COPY Blocks.json DESTINATION ${CMAKE_BINARY_DIR} )

# find_package(Boost REQUIRED COMPONENTS json)
# set(Boost_USE_STATIC_RUNTIME ON)
# set(Boost_USE_MULTITHREADED OFF)
find_package(Boost REQUIRED)

find_package(GTest CONFIG REQUIRED)

add_library(compile_commands_classes STATIC
	src/join.hpp
	src/join.cpp
	src/clean.hpp
	src/clean.cpp
	src/CompileCommands.hpp
	src/CompileCommands.cpp

	src/boost_json.cpp
)
set_default_target_options(compile_commands_classes)

target_link_libraries(compile_commands_classes
	PUBLIC
	    AidKit
		# Boost::json
		Boost::headers
)
target_include_directories(compile_commands_classes
	PUBLIC
	    src/
)

add_executable(compile_commands
	src/main.cpp
)
set_default_target_options(compile_commands)

target_link_libraries(compile_commands
	PRIVATE
	    compile_commands_classes
)

add_executable(unit_tests
	test/CleanTests.cpp
	test/CompileCommandsTest.cpp
)
set_default_target_options(unit_tests)

target_link_libraries(unit_tests
	PRIVATE
	    compile_commands_classes
		GTest::gtest
		GTest::gtest_main
)
