set(SMARTPLAYLISTS_SOURCES
  playlistgenerator.cpp
  playlistgeneratorinserter.cpp
  playlistgeneratormimedata.cpp
  playlistquerygenerator.cpp
  smartplaylistquerywizardplugin.cpp
  smartplaylistquerywizardpluginsortpage.cpp
  smartplaylistquerywizardpluginsearchpage.cpp
  smartplaylistsearch.cpp
  smartplaylistsearchpreview.cpp
  smartplaylistsearchterm.cpp
  smartplaylistsearchtermwidget.cpp
  smartplaylistsearchtermwidgetoverlay.cpp
  smartplaylistsmodel.cpp
  smartplaylistsviewcontainer.cpp
  smartplaylistsview.cpp
  smartplaylistwizard.cpp
  smartplaylistwizardplugin.cpp
  smartplaylistwizardtypepage.cpp
  smartplaylistwizardfinishpage.cpp
)

set(SMARTPLAYLISTS_HEADERS
  playlistgenerator.h
  playlistgeneratorinserter.h
  playlistquerygenerator.h
  playlistgeneratormimedata.h
  smartplaylistquerywizardplugin.h
  smartplaylistquerywizardpluginsortpage.h
  smartplaylistquerywizardpluginsearchpage.h
  smartplaylistsearchpreview.h
  smartplaylistsearchtermwidget.h
  smartplaylistsearchtermwidgetoverlay.h
  smartplaylistsmodel.h
  smartplaylistsviewcontainer.h
  smartplaylistsview.h
  smartplaylistwizard.h
  smartplaylistwizardplugin.h
  smartplaylistwizardtypepage.h
  smartplaylistwizardfinishpage.h
)

set(SMARTPLAYLISTS_UI
  smartplaylistquerysearchpage.ui
  smartplaylistquerysortpage.ui
  smartplaylistsearchpreview.ui
  smartplaylistsearchtermwidget.ui
  smartplaylistsviewcontainer.ui
  smartplaylistwizardfinishpage.ui
)

qt_wrap_cpp(SMARTPLAYLISTS_SOURCES ${SMARTPLAYLISTS_HEADERS})
qt_wrap_ui(SMARTPLAYLISTS_SOURCES ${SMARTPLAYLISTS_UI})

add_library(strawberry_smartplaylists STATIC ${SMARTPLAYLISTS_SOURCES})

target_include_directories(strawberry_smartplaylists PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_smartplaylists PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
  strawberry_filterparser
  strawberry_collection
  strawberry_playlist
)
