set(PLAYLISTPARSERS_SOURCES
  parserbase.cpp
  playlistparser.cpp
  asxiniparser.cpp
  asxparser.cpp
  cueparser.cpp
  m3uparser.cpp
  plsparser.cpp
  wplparser.cpp
  xmlparser.cpp
  xspfparser.cpp
)

set(PLAYLISTPARSERS_HEADERS
  parserbase.h
  playlistparser.h
  asxiniparser.h
  asxparser.h
  cueparser.h
  m3uparser.h
  plsparser.h
  wplparser.h
  xmlparser.h
  xspfparser.h
)

qt_wrap_cpp(PLAYLISTPARSERS_SOURCES ${PLAYLISTPARSERS_HEADERS})

add_library(strawberry_playlistparsers STATIC ${PLAYLISTPARSERS_SOURCES})

target_include_directories(strawberry_playlistparsers PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_playlistparsers PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  strawberry_utilities
  strawberry_core
  strawberry_tagreader
  strawberry_collection
)
