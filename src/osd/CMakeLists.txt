set(OSD_SOURCES osdbase.cpp osdpretty.cpp)
set(OSD_HEADERS osdbase.h osdpretty.h)
set(OSD_UI osdpretty.ui)

if(APPLE)
  list(APPEND OSD_SOURCES osdmac.mm)
  list(APPEND OSD_HEADERS osdmac.h)
endif()

if(HAVE_DBUS)
  list(APPEND OSD_SOURCES osddbus.cpp)
  list(APPEND OSD_HEADERS osddbus.h)
  qt_add_dbus_interface(OSD_SOURCES org.freedesktop.Notifications.xml notification)
endif()

qt_wrap_cpp(OSD_SOURCES ${OSD_HEADERS})
qt_wrap_ui(OSD_SOURCES ${OSD_UI})

add_library(strawberry_osd STATIC ${OSD_SOURCES})

target_include_directories(strawberry_osd PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

if(HAVE_QPA_QPLATFORMNATIVEINTERFACE_H)
  target_include_directories(strawberry_osd SYSTEM PRIVATE ${Qt${QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS})
endif()

target_link_libraries(strawberry_osd PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  PkgConfig::SQLITE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  $<$<BOOL:${HAVE_DBUS}>:Qt${QT_VERSION_MAJOR}::DBus>
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_systemtrayicon
)
