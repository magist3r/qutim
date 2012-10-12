if(NOT ANDROID)
	message(STATUS "Android integration will be skipped")
	return()
endif()

find_package( Qt4 COMPONENTS QtDeclarative QtOpenGL)
if(NOT QT_QTDECLARATIVE_FOUND OR NOT QT_QTOPENGL_FOUND)
	message(STATUS "Declarative libraries not found. Android integration will be skipped")
	return()
endif()

INCLUDE(FindPkgConfig)

FIND_PACKAGE( Qt4 COMPONENTS QtDBus)
if(NOT QT_QTDBUS_FOUND)
	message(STATUS "QtDBus libraries not found. Android integration will be skipped")
	return()
endif()

FILE( GLOB PLUGINS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" "${CMAKE_CURRENT_SOURCE_DIR}/*" )

qutim_add_plugin(meegoapplicationwindow
	DISPLAY_NAME "Meego application window"
	DESCRIPTION "Main window of application"
	QT_LIBRARIES DECLARATIVE OPENGL WEBKIT DBUS
	LINK_LIBRARIES qutim-adiumwebview
)
