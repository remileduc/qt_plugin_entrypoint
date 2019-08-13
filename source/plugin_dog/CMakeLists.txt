cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(PLUGINDOG_SOURCES
	PluginDog.hpp
	PluginDog.cpp
	DogFriendInterface.hpp
)

add_library(PluginDog SHARED
	${PLUGINDOG_SOURCES}
)
target_include_directories(PluginDog PRIVATE
	../utils
)
target_link_libraries(PluginDog
	# Qt
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	# utils
	utils
)

source_group("PluginDog" FILES ${PLUGINDOG_SOURCES})
