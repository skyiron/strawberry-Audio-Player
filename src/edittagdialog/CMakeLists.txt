set(EDITTAGDIALOG_SOURCES
  edittagdialog.cpp
  trackselectiondialog.cpp
)

set(EDITTAGDIALOG_HEADERS
  edittagdialog.h
  trackselectiondialog.h
)

set(EDITTAGDIALOG_UI
  edittagdialog.ui
  trackselectiondialog.ui
)

qt_wrap_cpp(EDITTAGDIALOG_SOURCES ${EDITTAGDIALOG_HEADERS})
qt_wrap_ui(EDITTAGDIALOG_SOURCES ${EDITTAGDIALOG_UI})

add_library(strawberry_edittagdialog STATIC ${EDITTAGDIALOG_SOURCES})

target_include_directories(strawberry_edittagdialog PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_edittagdialog PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
  strawberry_utilities
  strawberry_tagreader
  strawberry_covermanager
  strawberry_widgets
  strawberry_collection
  strawberry_lyrics
)
