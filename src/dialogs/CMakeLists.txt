set(DIALOGS_SOURCES
  about.cpp
  console.cpp
  errordialog.cpp
  addstreamdialog.cpp
  userpassdialog.cpp
  deleteconfirmationdialog.cpp
  lastfmimportdialog.cpp
  messagedialog.cpp
  snapdialog.cpp
  saveplaylistsdialog.cpp
)

set(DIALOGS_HEADERS
  about.h
  errordialog.h
  console.h
  addstreamdialog.h
  userpassdialog.h
  deleteconfirmationdialog.h
  lastfmimportdialog.h
  messagedialog.h
  snapdialog.h
  saveplaylistsdialog.h
)

set(DIALOGS_UI
  about.ui
  errordialog.ui
  console.ui
  addstreamdialog.ui
  userpassdialog.ui
  lastfmimportdialog.ui
  messagedialog.ui
  saveplaylistsdialog.ui
)

qt_wrap_cpp(DIALOGS_SOURCES ${DIALOGS_HEADERS})
qt_wrap_ui(DIALOGS_SOURCES ${DIALOGS_UI})

add_library(strawberry_dialogs STATIC ${DIALOGS_SOURCES})

target_include_directories(strawberry_dialogs PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_dialogs PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
)
