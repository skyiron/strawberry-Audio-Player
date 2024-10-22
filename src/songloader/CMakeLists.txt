set(SONGLOADER_SOURCES songloader.cpp)
set(SONGLOADER_HEADERS songloader.h)

qt_wrap_cpp(SONGLOADER_SOURCES ${SONGLOADER_HEADERS})

add_library(strawberry_songloader STATIC ${SONGLOADER_SOURCES})

target_include_directories(strawberry_songloader PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_songloader PRIVATE
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
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_collection
  strawberry_tagreader
  strawberry_playlistparsers
)
