cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(MAINAPP_SOURCES
	MainApp.cpp
	MainApp.hpp
	MainApp.ui
	main.cpp
)

add_executable(MainApp WIN32
	${MAINAPP_SOURCES}
)
target_compile_definitions(MainApp PRIVATE
	utils_IMPORT
)
target_include_directories(MainApp PRIVATE
	../utils
)
target_link_libraries(MainApp
	# Qt
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	# utils
	utils
)

#########################
# Copy Plugins
list(APPEND PLUGIN_LIST "utils")
foreach(plugin IN LISTS PLUGIN_LIST)
	add_custom_command(TARGET MainApp POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy
			"$<TARGET_FILE:${plugin}>"
			"$<TARGET_FILE_DIR:MainApp>"
		COMMENT "Copying ${plugin} to plugin directory"
	)
	# run windeployqt
	if(WIN32)
		add_custom_command(TARGET MainApp POST_BUILD
			COMMAND "${QT_ROOT_PATH}/bin/windeployqt.exe"
				$<$<CONFIG:debug>:--debug>$<$<CONFIG:release>:--release>
				--verbose 0
				--no-compiler-runtime
				--dir "$<TARGET_FILE_DIR:MainApp>"
				"$<TARGET_FILE:${plugin}>"
			COMMENT "Deploying Qt for ${plugin}..."
		)
	endif()
endforeach()
# run windeployqt
if(WIN32)
	add_custom_command(TARGET MainApp POST_BUILD
		COMMAND "${QT_ROOT_PATH}/bin/windeployqt.exe"
			$<$<CONFIG:debug>:--debug>$<$<CONFIG:release>:--release>
			--verbose 0
			--no-compiler-runtime
			--dir "$<TARGET_FILE_DIR:MainApp>"
			"$<TARGET_FILE:MainApp>"
		COMMENT "Deploying Qt for MainApp..."
	)
endif()

source_group("MainApp" FILES ${MAINAPP_SOURCES})
