cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(UTILS_SOURCES
	PluginInterface.hpp
	utils.cpp
	utils.hpp
)

add_library(utils STATIC
	${UTILS_SOURCES}
)
target_link_libraries(utils
	# Qt
	Qt5::Core
)

source_group("utils" FILES ${UTILS_SOURCES})
