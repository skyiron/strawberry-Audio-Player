set(SPOTIFY_SOURCES
  spotifyservice.cpp
  spotifybaserequest.cpp
  spotifyrequest.cpp
  spotifyfavoriterequest.cpp
)

set(SPOTIFY_HEADERS
  spotifyservice.h
  spotifybaserequest.h
  spotifyrequest.h
  spotifyfavoriterequest.h
)

qt_wrap_cpp(SPOTIFY_SOURCES ${SPOTIFY_HEADERS})

add_library(strawberry_spotify STATIC ${SPOTIFY_SOURCES})

target_include_directories(strawberry_spotify PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_spotify PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_streaming
  strawberry_collection
)
