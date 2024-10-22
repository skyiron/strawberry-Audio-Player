set(MUSICBRAINZ_SOURCES
  acoustidclient.cpp
  musicbrainzclient.cpp
  tagfetcher.cpp
)

set(MUSICBRAINZ_HEADERS
  acoustidclient.h
  musicbrainzclient.h
  tagfetcher.h
)

qt_wrap_cpp(MUSICBRAINZ_SOURCES ${MUSICBRAINZ_HEADERS})

add_library(strawberry_musicbrainz STATIC ${MUSICBRAINZ_SOURCES})

target_include_directories(strawberry_musicbrainz PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_musicbrainz PRIVATE
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
  Qt${QT_VERSION_MAJOR}::Gui
  strawberry_utilities
  strawberry_core
  strawberry_engine
)
