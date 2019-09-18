cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(UTILS_SOURCES
	PluginInterface.hpp
	PluginManager.cpp
	PluginManager.hpp
)

add_library(utils SHARED
	${UTILS_SOURCES}
)
set_target_properties(utils PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_compile_definitions(utils PRIVATE
	utils_EXPORT
)
target_link_libraries(utils
	# Qt
	Qt5::Core
)

source_group("utils" FILES ${UTILS_SOURCES})
