cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(PLUGINCAT_SOURCES
	PluginCat.hpp
	PluginCat.cpp
)

add_library(PluginCat SHARED
	${PLUGINCAT_SOURCES}
)
target_include_directories(PluginCat PRIVATE
	../utils
)
target_link_libraries(PluginCat
	# Qt
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	# utils
	utils
)

source_group("PluginCat" FILES ${PLUGINCAT_SOURCES})
