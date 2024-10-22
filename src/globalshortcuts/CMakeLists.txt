set(GLOBALSHORTCUTS_SOURCES globalshortcutsmanager.cpp globalshortcutsbackend.cpp globalshortcutgrabber.cpp)
set(GLOBALSHORTCUTS_HEADERS globalshortcutsmanager.h globalshortcutsbackend.h globalshortcutgrabber.h)
set(GLOBALSHORTCUTS_UI globalshortcutgrabber.ui)

if(HAVE_KDE_GLOBALSHORTCUTS)
  list(APPEND GLOBALSHORTCUTS_SOURCES globalshortcutsbackend-kde.cpp globalshortcutsbackend-gnome.cpp globalshortcutsbackend-mate.cpp)
  list(APPEND GLOBALSHORTCUTS_HEADERS globalshortcutsbackend-kde.h globalshortcutsbackend-gnome.h globalshortcutsbackend-mate.h)
endif()

if(HAVE_X11_GLOBALSHORTCUTS)
  list(APPEND GLOBALSHORTCUTS_SOURCES globalshortcutsbackend-x11.cpp globalshortcut.cpp globalshortcut-x11.cpp)
  list(APPEND GLOBALSHORTCUTS_HEADERS globalshortcutsbackend-x11.h globalshortcut.h)
endif()

if(APPLE)
  list(APPEND GLOBALSHORTCUTS_SOURCES globalshortcutsbackend-macos.mm globalshortcutgrabber.mm)
  list(APPEND GLOBALSHORTCUTS_HEADERS globalshortcutsbackend-macos.h globalshortcutgrabber.h)
endif()

if(WIN32)
  list(APPEND GLOBALSHORTCUTS_SOURCES globalshortcutsbackend-win.cpp globalshortcut.cpp globalshortcut-win.cpp)
  list(APPEND GLOBALSHORTCUTS_HEADERS globalshortcutsbackend-win.h globalshortcut.h)
endif()

if(HAVE_KDE_GLOBALSHORTCUTS)
  qt_add_dbus_interface(GLOBALSHORTCUTS_SOURCES org.kde.KGlobalAccel.xml kglobalaccel)
  qt_add_dbus_interface(GLOBALSHORTCUTS_SOURCES org.kde.KGlobalAccel.Component.xml kglobalaccelcomponent)
endif()

if(HAVE_GNOME_GLOBALSHORTCUTS)
  qt_add_dbus_interface(GLOBALSHORTCUTS_SOURCES org.gnome.SettingsDaemon.MediaKeys.xml gnomesettingsdaemon)
endif()

if(HAVE_MATE_GLOBALSHORTCUTS)
  qt_add_dbus_interface(GLOBALSHORTCUTS_SOURCES org.mate.SettingsDaemon.MediaKeys.xml matesettingsdaemon)
endif()

qt_wrap_cpp(GLOBALSHORTCUTS_SOURCES ${GLOBALSHORTCUTS_HEADERS})
qt_wrap_ui(GLOBALSHORTCUTS_SOURCES ${GLOBALSHORTCUTS_UI})

add_library(strawberry_globalshortcuts STATIC ${GLOBALSHORTCUTS_SOURCES})

target_include_directories(strawberry_globalshortcuts PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_globalshortcuts PRIVATE
  $<$<BOOL:${HAVE_X11_GLOBALSHORTCUTS}>:X11::X11_xcb>
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  $<$<BOOL:${HAVE_DBUS}>:Qt${QT_VERSION_MAJOR}::DBus>
  strawberry_core
)

if(APPLE)
  target_link_libraries(strawberry_globalshortcuts PRIVATE
    "-framework ScriptingBridge"
    strawberry_macstartup
  )
endif()
