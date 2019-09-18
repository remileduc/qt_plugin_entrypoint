cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(PLUGINFROG_SOURCES
	DogFriend.cpp
	DogFriend.hpp
	PluginFrog.cpp
	PluginFrog.hpp
)

add_library(PluginFrog SHARED
	${PLUGINFROG_SOURCES}
)
target_compile_definitions(PluginFrog PRIVATE
	utils_IMPORT
)
target_include_directories(PluginFrog PRIVATE
	../utils
)
target_link_libraries(PluginFrog
	# Qt
	Qt5::Core
	# utils
	utils
)

source_group("PluginFrog" FILES ${PLUGINFROG_SOURCES})
