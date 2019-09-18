cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(PLUGINCAT_SOURCES
	CatInfo.cpp
	CatInfo.hpp
	DogEnemy.cpp
	DogEnemy.hpp
	PluginCat.cpp
	PluginCat.hpp
)

add_library(PluginCat SHARED
	${PLUGINCAT_SOURCES}
)
target_compile_definitions(PluginCat PRIVATE
	utils_IMPORT
)
target_include_directories(PluginCat PRIVATE
	../utils
)
target_link_libraries(PluginCat
	# Qt
	Qt5::Core
	# utils
	utils
)

source_group("PluginCat" FILES ${PLUGINCAT_SOURCES})
