set(PLAYER_SOURCES
  playerinterface.cpp
  player.cpp
)

set(PLAYER_HEADERS
  playerinterface.h
  player.h
)

qt_wrap_cpp(PLAYER_SOURCES ${PLAYER_HEADERS})

add_library(strawberry_player STATIC ${PLAYER_SOURCES})

target_include_directories(strawberry_player PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_player PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  PkgConfig::GSTREAMER
  PkgConfig::GSTREAMER_BASE
  PkgConfig::GSTREAMER_AUDIO
  PkgConfig::GSTREAMER_APP
  PkgConfig::GSTREAMER_TAG
  PkgConfig::GSTREAMER_PBUTILS
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
  strawberry_engine
  strawberry_collection
  strawberry_playlist
  strawberry_equalizer
  strawberry_analyzer
)
