set(COVERMANAGER_SOURCES
  albumcovermanager.cpp
  albumcovermanagerlist.cpp
  albumcoverloader.cpp
  albumcoverloaderoptions.cpp
  albumcoverfetcher.cpp
  albumcoverfetchersearch.cpp
  albumcoversearcher.cpp
  albumcoverexport.cpp
  albumcoverexporter.cpp
  albumcoverchoicecontroller.cpp
  coverprovider.cpp
  coverproviders.cpp
  coversearchstatistics.cpp
  coversearchstatisticsdialog.cpp
  coverexportrunnable.cpp
  currentalbumcoverloader.cpp
  coverfromurldialog.cpp
  jsoncoverprovider.cpp
  lastfmcoverprovider.cpp
  musicbrainzcoverprovider.cpp
  discogscoverprovider.cpp
  deezercoverprovider.cpp
  musixmatchcoverprovider.cpp
  opentidalcoverprovider.cpp
)

set(COVERMANAGER_HEADERS
  albumcovermanager.h
  albumcovermanagerlist.h
  albumcoverloader.h
  albumcoverfetcher.h
  albumcoverfetchersearch.h
  albumcoversearcher.h
  albumcoverexport.h
  albumcoverexporter.h
  albumcoverchoicecontroller.h
  coverprovider.h
  coverproviders.h
  coversearchstatisticsdialog.h
  coverexportrunnable.h
  currentalbumcoverloader.h
  coverfromurldialog.h
  jsoncoverprovider.h
  lastfmcoverprovider.h
  musicbrainzcoverprovider.h
  discogscoverprovider.h
  deezercoverprovider.h
  musixmatchcoverprovider.h
  opentidalcoverprovider.h
)

set(COVERMANAGER_UI
  albumcoverexport.ui
  albumcovermanager.ui
  albumcoversearcher.ui
  coversearchstatisticsdialog.ui
  coverfromurldialog.ui
)

if(HAVE_TIDAL)
  list(APPEND COVERMANAGER_SOURCES tidalcoverprovider.cpp)
  list(APPEND COVERMANAGER_HEADERS tidalcoverprovider.h)
endif()

if(HAVE_SPOTIFY)
  list(APPEND COVERMANAGER_SOURCES spotifycoverprovider.cpp)
  list(APPEND COVERMANAGER_HEADERS spotifycoverprovider.h)
endif()

if(HAVE_QOBUZ)
  list(APPEND COVERMANAGER_SOURCES qobuzcoverprovider.cpp)
  list(APPEND COVERMANAGER_HEADERS qobuzcoverprovider.h)
endif()

qt_wrap_cpp(COVERMANAGER_SOURCES ${COVERMANAGER_HEADERS})
qt_wrap_ui(COVERMANAGER_SOURCES ${COVERMANAGER_UI})

add_library(strawberry_covermanager STATIC ${COVERMANAGER_SOURCES})

target_include_directories(strawberry_covermanager PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_covermanager PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_tagreader
  strawberry_collection
  strawberry_streaming
  strawberry_widgets
)

if(HAVE_SUBSONIC)
  target_link_libraries(strawberry_covermanager PRIVATE strawberry_subsonic)
endif()

if(HAVE_TIDAL)
  target_link_libraries(strawberry_covermanager PRIVATE strawberry_tidal)
endif()

if(HAVE_SPOTIFY)
  target_link_libraries(strawberry_covermanager PRIVATE strawberry_spotify)
endif()

if(HAVE_QOBUZ)
  target_link_libraries(strawberry_covermanager PRIVATE strawberry_qobuz)
endif()
