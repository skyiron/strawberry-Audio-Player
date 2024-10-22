set(ORGANIZE_SOURCES
  organize.cpp
  organizeformat.cpp
  organizeformatvalidator.cpp
  organizesyntaxhighlighter.cpp
  organizedialog.cpp
  organizeerrordialog.cpp
)

set(ORGANIZE_HEADERS
  organize.h
  organizeformatvalidator.h
  organizesyntaxhighlighter.h
  organizedialog.h
  organizeerrordialog.h
)

set(ORGANIZE_UI
  organizedialog.ui
  organizeerrordialog.ui
)

qt_wrap_cpp(ORGANIZE_SOURCES ${ORGANIZE_HEADERS})
qt_wrap_ui(ORGANIZE_SOURCES ${ORGANIZE_UI})

add_library(strawberry_organize STATIC ${ORGANIZE_SOURCES})

target_include_directories(strawberry_organize PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_organize PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  PkgConfig::GSTREAMER
  PkgConfig::GSTREAMER_BASE
  PkgConfig::GSTREAMER_AUDIO
  PkgConfig::GSTREAMER_APP
  PkgConfig::GSTREAMER_TAG
  PkgConfig::GSTREAMER_PBUTILS
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_tagreader
  strawberry_widgets
  strawberry_collection
)
