set(SCROBBLER_SOURCES
  audioscrobbler.cpp
  scrobblersettingsservice.cpp
  scrobblerservice.cpp
  scrobblercache.cpp
  scrobblercacheitem.cpp
  scrobblemetadata.cpp
  scrobblingapi20.cpp
  lastfmscrobbler.cpp
  librefmscrobbler.cpp
  listenbrainzscrobbler.cpp
  lastfmimport.cpp
)

set(SCROBBLER_HEADERS
  audioscrobbler.h
  scrobblersettingsservice.h
  scrobblerservice.h
  scrobblercache.h
  scrobblingapi20.h
  lastfmscrobbler.h
  librefmscrobbler.h
  listenbrainzscrobbler.h
  lastfmimport.h
)

if(HAVE_SUBSONIC)
  list(APPEND SCROBBLER_SOURCES subsonicscrobbler.cpp)
  list(APPEND SCROBBLER_HEADERS subsonicscrobbler.h)
endif()

qt_wrap_cpp(SCROBBLER_SOURCES ${SCROBBLER_HEADERS})

add_library(strawberry_scrobbler STATIC ${SCROBBLER_SOURCES})

target_include_directories(strawberry_scrobbler PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_scrobbler PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
)

if(HAVE_SUBSONIC)
  target_link_libraries(strawberry_scrobbler PRIVATE strawberry_subsonic)
endif()
