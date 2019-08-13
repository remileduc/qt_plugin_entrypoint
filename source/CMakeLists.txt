cmake_minimum_required(VERSION 3.10)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#########################
# C++
enable_language("CXX")
include(CheckIncludeFileCXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
	add_compile_options(
		# generic
		"-Wall" "-Wextra" "-pedantic"
	)
	# debug
	if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
		add_compile_options("-g" "-O0")
	# release
	else()
		add_compile_options("-O3")
	endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	include(ProcessorCount)
	ProcessorCount(N)
	if (N GREATER 8)
		set(N 8)
	endif()
	add_compile_options(
		# generic
		"/Zc:__cplusplus" "/cgthreads${N}" "/MP" "/W4"
		# debug
		"$<$<CONFIG:debug>:/DEBUG>"
		"$<$<CONFIG:debug>:/Od>"
		# release
		"$<$<CONFIG:release>:/O2>"
		"$<$<CONFIG:release>:/GL>"
	)
	add_link_options(
		# release
		"$<$<CONFIG:release>:/LTCG>"
	)
endif()

#########################
# Qt setup
if(WIN32)
	set(QT_ROOT_PATH "C:/Qt/5.12.2/msvc2017_64")
	set(CMAKE_PREFIX_PATH ${QT_ROOT_PATH})
endif()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#########################
# Project
project(MainApp CXX)

#########################
# utils
add_subdirectory("utils")

#########################
# PluginCat
add_subdirectory("plugin_cat")
#########################
# PluginDog
add_subdirectory("plugin_dog")
#########################
# PluginFrog
add_subdirectory("plugin_frog")

#########################
# MainApp
set(PLUGIN_LIST
	PluginCat
	PluginDog
	PluginFrog
)
add_subdirectory("main_app")

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT MainApp)
