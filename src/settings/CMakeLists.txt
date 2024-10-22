set(SETTINGS_SOURCES
  settingsdialog.cpp
  settingspage.cpp
  settingsitemdelegate.cpp
  behavioursettingspage.cpp
  collectionsettingspage.cpp
  collectionsettingsdirectorymodel.cpp
  backendsettingspage.cpp
  playlistsettingspage.cpp
  scrobblersettingspage.cpp
  coverssettingspage.cpp
  lyricssettingspage.cpp
  networkproxysettingspage.cpp
  appearancesettingspage.cpp
  contextsettingspage.cpp
  notificationssettingspage.cpp
  transcodersettingspage.cpp
)

set(SETTINGS_HEADERS
  settingsdialog.h
  settingspage.h
  settingsitemdelegate.h
  behavioursettingspage.h
  collectionsettingspage.h
  collectionsettingsdirectorymodel.h
  backendsettingspage.h
  playlistsettingspage.h
  scrobblersettingspage.h
  coverssettingspage.h
  lyricssettingspage.h
  networkproxysettingspage.h
  appearancesettingspage.h
  contextsettingspage.h
  notificationssettingspage.h
  transcodersettingspage.h
)

set(SETTINGS_UI
  settingsdialog.ui
  behavioursettingspage.ui
  collectionsettingspage.ui
  backendsettingspage.ui
  contextsettingspage.ui
  playlistsettingspage.ui
  scrobblersettingspage.ui
  coverssettingspage.ui
  lyricssettingspage.ui
  networkproxysettingspage.ui
  appearancesettingspage.ui
  notificationssettingspage.ui
  transcodersettingspage.ui
)

if(HAVE_MOODBAR)
  list(APPEND SETTINGS_SOURCES moodbarsettingspage.cpp)
  list(APPEND SETTINGS_HEADERS moodbarsettingspage.h)
  list(APPEND SETTINGS_UI moodbarsettingspage.ui)
endif()

if(HAVE_SUBSONIC)
  list(APPEND SETTINGS_SOURCES subsonicsettingspage.cpp)
  list(APPEND SETTINGS_HEADERS subsonicsettingspage.h)
  list(APPEND SETTINGS_UI subsonicsettingspage.ui)
endif()

if(HAVE_TIDAL)
  list(APPEND SETTINGS_SOURCES tidalsettingspage.cpp)
  list(APPEND SETTINGS_HEADERS tidalsettingspage.h)
  list(APPEND SETTINGS_UI tidalsettingspage.ui)
endif()

if(HAVE_SPOTIFY)
  list(APPEND SETTINGS_SOURCES spotifysettingspage.cpp)
  list(APPEND SETTINGS_HEADERS spotifysettingspage.h)
  list(APPEND SETTINGS_UI spotifysettingspage.ui)
endif()

if(HAVE_QOBUZ)
  list(APPEND SETTINGS_SOURCES qobuzsettingspage.cpp)
  list(APPEND SETTINGS_HEADERS qobuzsettingspage.h)
  list(APPEND SETTINGS_UI qobuzsettingspage.ui)
endif()

if(HAVE_GLOBALSHORTCUTS)
  list(APPEND SETTINGS_SOURCES globalshortcutssettingspage.cpp)
  list(APPEND SETTINGS_HEADERS globalshortcutssettingspage.h)
  list(APPEND SETTINGS_UI globalshortcutssettingspage.ui)
endif()

qt_wrap_cpp(SETTINGS_SOURCES ${SETTINGS_HEADERS})
qt_wrap_ui(SETTINGS_SOURCES ${SETTINGS_UI})

add_library(strawberry_settings STATIC ${SETTINGS_SOURCES})

target_include_directories(strawberry_settings PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_settings PRIVATE
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
  strawberry_engine
  strawberry_covermanager
  strawberry_lyrics
  strawberry_widgets
  strawberry_osd
  strawberry_transcoder
  strawberry_streaming
)

if(HAVE_MOODBAR)
  target_link_libraries(strawberry_settings PRIVATE strawberry_moodbar)
endif()

if(HAVE_GLOBALSHORTCUTS)
  target_link_libraries(strawberry_settings PRIVATE strawberry_globalshortcuts)
endif()
