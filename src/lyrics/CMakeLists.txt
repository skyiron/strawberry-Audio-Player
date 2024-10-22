set(LYRICS_SOURCES
  lyricsproviders.cpp
  lyricsprovider.cpp
  lyricssearchrequest.h
  lyricssearchresult.h
  lyricsfetcher.cpp
  lyricsfetchersearch.cpp
  jsonlyricsprovider.cpp
  htmllyricsprovider.cpp
  ovhlyricsprovider.cpp
  lololyricsprovider.cpp
  geniuslyricsprovider.cpp
  musixmatchlyricsprovider.cpp
  chartlyricsprovider.cpp
  songlyricscomlyricsprovider.cpp
  azlyricscomlyricsprovider.cpp
  elyricsnetlyricsprovider.cpp
  letraslyricsprovider.cpp
  lyricfindlyricsprovider.cpp
)

set(LYRICS_HEADERS
  lyricsproviders.h
  lyricsprovider.h
  lyricsfetcher.h
  lyricsfetchersearch.h
  jsonlyricsprovider.h
  htmllyricsprovider.h
  ovhlyricsprovider.h
  lololyricsprovider.h
  geniuslyricsprovider.h
  musixmatchlyricsprovider.h
  chartlyricsprovider.h
  songlyricscomlyricsprovider.h
  azlyricscomlyricsprovider.h
  elyricsnetlyricsprovider.h
  letraslyricsprovider.h
  lyricfindlyricsprovider.h
)

qt_wrap_cpp(LYRICS_SOURCES ${LYRICS_HEADERS})

add_library(strawberry_lyrics STATIC ${LYRICS_SOURCES})

target_include_directories(strawberry_lyrics PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_lyrics PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_providers
)
