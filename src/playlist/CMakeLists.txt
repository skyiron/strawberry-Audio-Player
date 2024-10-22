set(PLAYLIST_SOURCES
  playlist.cpp
  playlistbackend.cpp
  playlistcontainer.cpp
  playlistdelegates.cpp
  playlistfilter.cpp
  playlistheader.cpp
  playlistitem.cpp
  playlistitemmimedata.cpp
  playlistlistcontainer.cpp
  playlistlistmodel.cpp
  playlistlistsortfiltermodel.cpp
  playlistlistview.cpp
  playlistmanagerinterface.cpp
  playlistmanager.cpp
  playlistsaveoptionsdialog.cpp
  playlistsequence.cpp
  playlisttabbar.cpp
  playlistview.cpp
  playlistproxystyle.cpp
  songloaderinserter.cpp
  songplaylistitem.cpp
  dynamicplaylistcontrols.cpp
  playlistundocommandbase.cpp
  playlistundocommandinsertitems.cpp
  playlistundocommandremoveitems.cpp
  playlistundocommandmoveitems.cpp
  playlistundocommandreorderitems.cpp
  playlistundocommandsortitems.cpp
  playlistundocommandshuffleitems.cpp
)

set(PLAYLIST_HEADERS
  playlist.h
  playlistbackend.h
  playlistcontainer.h
  playlistdelegates.h
  playlistfilter.h
  playlistheader.h
  playlistlistcontainer.h
  playlistlistmodel.h
  playlistlistview.h
  playlistlistsortfiltermodel.h
  playlistmanagerinterface.h
  playlistmanager.h
  playlistsaveoptionsdialog.h
  playlistsequence.h
  playlisttabbar.h
  playlistview.h
  playlistproxystyle.h
  playlistitemmimedata.h
  songloaderinserter.h
  dynamicplaylistcontrols.h
)

set(PLAYLIST_UI
  playlistcontainer.ui
  playlistlistcontainer.ui
  playlistsaveoptionsdialog.ui
  playlistsequence.ui
  dynamicplaylistcontrols.ui
)

qt_wrap_cpp(PLAYLIST_SOURCES ${PLAYLIST_HEADERS})
qt_wrap_ui(PLAYLIST_SOURCES ${PLAYLIST_UI})

add_library(strawberry_playlist STATIC ${PLAYLIST_SOURCES})

target_include_directories(strawberry_playlist PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_playlist PRIVATE
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
  strawberry_mimedata
  strawberry_songloader
  strawberry_tagreader
  strawberry_collection
  strawberry_dialogs
  strawberry_queue
  strawberry_filterparser
  strawberry_covermanager
  strawberry_widgets
  strawberry_player
  strawberry_smartplaylists
  strawberry_radios
  strawberry_device
)

if(HAVE_MOODBAR)
  target_link_libraries(strawberry_playlist PRIVATE strawberry_moodbar)
endif()
