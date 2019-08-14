cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(PLUGINFROG_SOURCES
	PluginFrog.hpp
	PluginFrog.cpp
	DogFriend.hpp
	DogFriend.cpp
	DogInterface.hpp
)

add_library(PluginFrog SHARED
	${PLUGINFROG_SOURCES}
)
target_include_directories(PluginFrog PRIVATE
	../utils
)
target_link_libraries(PluginFrog
	# Qt
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	# utils
	utils
)

source_group("PluginFrog" FILES ${PLUGINFROG_SOURCES})
