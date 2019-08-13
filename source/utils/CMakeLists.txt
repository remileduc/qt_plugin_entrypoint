cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(UTILS_SOURCES
	PluginInterface.hpp
	utils.hpp
	utils.cpp
)

add_library(utils STATIC
	${UTILS_SOURCES}
)
target_link_libraries(utils
	# Qt
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)

source_group("utils" FILES ${UTILS_SOURCES})
