cmake_minimum_required(VERSION 3.13)

project(strawberry C CXX)

if(APPLE)
  enable_language(OBJC OBJCXX)
endif()

if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

include(CheckCXXCompilerFlag)
include(CheckCXXSourceRuns)
include(CheckIncludeFiles)
include(FindPkgConfig)
include(cmake/Version.cmake)
include(cmake/OptionalComponent.cmake)
include(cmake/OptionalSource.cmake)
include(cmake/ParseArguments.cmake)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(LINUX ON)
endif()

if(LINUX)
  include(cmake/Rpm.cmake)
  include(cmake/Deb.cmake)
endif()

if(APPLE)
  include(cmake/Dmg.cmake)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if(CMAKE_BUILD_TYPE MATCHES "Release")
  add_definitions(-DNDEBUG)
  set(ENABLE_DEBUG_OUTPUT_DEFAULT OFF)
else()
  set(ENABLE_DEBUG_OUTPUT_DEFAULT ON)
endif()

if(APPLE OR WIN32)
  set(USE_BUNDLE_DEFAULT ON)
else()
  set(USE_BUNDLE_DEFAULT OFF)
endif()

if(WIN32)
  if(CMAKE_BUILD_TYPE MATCHES "Release")
    set(ENABLE_WIN32_CONSOLE_DEFAULT OFF)
  else()
    set(ENABLE_WIN32_CONSOLE_DEFAULT ON)
  endif()
endif()

option(BUILD_WERROR "Build with -Werror" OFF)
option(USE_RPATH "Use RPATH" APPLE)
option(USE_INSTALL_PREFIX "Look for data in CMAKE_INSTALL_PREFIX" ON)
option(INSTALL_TRANSLATIONS "Install translations" OFF)
option(ENABLE_DEBUG_OUTPUT "Enable debug output" ${ENABLE_DEBUG_OUTPUT_DEFAULT})
option(USE_BUNDLE "Bundle dependencies" ${USE_BUNDLE_DEFAULT})

if(WIN32)
  option(ENABLE_WIN32_CONSOLE "Show the windows console even outside Debug mode" ${ENABLE_WIN32_CONSOLE_DEFAULT})
endif()

if(MSVC)
  set(CMAKE_C_STANDARD 99)
else()
  set(CMAKE_C_STANDARD 11)
endif()

set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  list(APPEND COMPILE_OPTIONS /MP)
else()
  list(APPEND COMPILE_OPTIONS
    $<$<COMPILE_LANGUAGE:C>:-std=c11>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
    -Wall
    -Wextra
    -Wpedantic
    -Wunused
    -Wshadow
    -Wundef
    -Wuninitialized
    -Wredundant-decls
    -Wcast-align
    -Winit-self
    -Wmissing-include-dirs
    -Wmissing-declarations
    -Wstrict-overflow=2
    -Wunused-parameter
    -Wformat=2
    -Wdisabled-optimization
    $<$<COMPILE_LANGUAGE:CXX>:-Woverloaded-virtual>
    $<$<COMPILE_LANGUAGE:CXX>:-Wold-style-cast>
  )
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    list(APPEND COMPILE_OPTIONS -Wno-unused-command-line-argument)
  endif()
endif()

add_compile_options(${COMPILE_OPTIONS})

add_definitions(
  -DBOOST_BIND_NO_PLACEHOLDERS
  -DQT_STRICT_ITERATORS
  -DQT_NO_CAST_FROM_BYTEARRAY
  -DQT_USE_QSTRINGBUILDER
  -DQT_NO_URL_CAST_FROM_STRING
  -DQT_NO_CAST_TO_ASCII
  -DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT
  -DQT_NO_FOREACH
  -DQT_ASCII_CAST_WARNINGS
  -DQT_NO_CAST_FROM_ASCII
  -DQT_NO_KEYWORDS
  -DQT_NO_SIGNALS_SLOTS_KEYWORDS
)

if(WIN32)
  add_definitions(-DUNICODE)
endif()

if(BUILD_WERROR)
  set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
endif()

if(NOT ENABLE_DEBUG_OUTPUT)
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

if(USE_RPATH)
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

find_program(CCACHE_EXECUTABLE NAMES ccache)
if(CCACHE_EXECUTABLE)
  message(STATUS "ccache found: will be used for compilation and linkage")
  SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_EXECUTABLE})
  SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_EXECUTABLE})
endif()

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
find_package(Backtrace)
if(Backtrace_FOUND)
  set(HAVE_BACKTRACE ON)
endif()
find_package(Boost CONFIG)
if(NOT Boost_FOUND)
  find_package(Boost REQUIRED)
endif()
find_package(ICU COMPONENTS uc i18n REQUIRED)
if(UNIX AND NOT APPLE)
  if(LINUX)
    find_package(ALSA REQUIRED)
  else()
    find_package(ALSA)
  endif()
  find_package(X11 COMPONENTS X11_xcb)
endif()
pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(GOBJECT REQUIRED IMPORTED_TARGET gobject-2.0)
if(NOT APPLE)
  pkg_check_modules(GIO REQUIRED IMPORTED_TARGET gio-2.0)
  if(GIO_FOUND AND UNIX)
    pkg_check_modules(GIO_UNIX IMPORTED_TARGET gio-unix-2.0)
  endif()
endif()
pkg_check_modules(LIBCDIO IMPORTED_TARGET libcdio)
pkg_check_modules(GSTREAMER REQUIRED IMPORTED_TARGET gstreamer-1.0)
pkg_check_modules(GSTREAMER_BASE REQUIRED IMPORTED_TARGET gstreamer-base-1.0)
pkg_check_modules(GSTREAMER_AUDIO REQUIRED IMPORTED_TARGET gstreamer-audio-1.0)
pkg_check_modules(GSTREAMER_APP REQUIRED IMPORTED_TARGET gstreamer-app-1.0)
pkg_check_modules(GSTREAMER_TAG REQUIRED IMPORTED_TARGET gstreamer-tag-1.0)
pkg_check_modules(GSTREAMER_PBUTILS REQUIRED IMPORTED_TARGET gstreamer-pbutils-1.0)
pkg_check_modules(SQLITE REQUIRED IMPORTED_TARGET sqlite3>=3.9)
if(UNIX AND NOT APPLE)
  pkg_check_modules(LIBPULSE IMPORTED_TARGET libpulse)
endif()
pkg_check_modules(CHROMAPRINT IMPORTED_TARGET libchromaprint>=1.4)
pkg_check_modules(FFTW3 IMPORTED_TARGET fftw3)
pkg_check_modules(LIBEBUR128 IMPORTED_TARGET libebur128)
pkg_check_modules(LIBGPOD IMPORTED_TARGET libgpod-1.0>=0.7.92)
pkg_check_modules(LIBMTP IMPORTED_TARGET libmtp>=1.0)
pkg_check_modules(GDK_PIXBUF IMPORTED_TARGET gdk-pixbuf-2.0)

find_package(TagLib 2.0)
if(TARGET TagLib::TagLib)
  set(TAGLIB_FOUND ON)
  set(TAGLIB_LIBRARIES TagLib::TagLib)
  set(HAVE_TAGLIB_DSFFILE ON)
  set(HAVE_TAGLIB_DSDIFFFILE ON)
else()
  pkg_check_modules(TAGLIB REQUIRED IMPORTED_TARGET taglib>=1.12)
endif()

find_package(GTest)

set(QT_VERSION_MAJOR 6)
set(QT_MIN_VERSION 6.4.0)
set(QT_DEFAULT_MAJOR_VERSION ${QT_VERSION_MAJOR})
set(QT_COMPONENTS Core Concurrent Gui Widgets Network Sql)
set(QT_OPTIONAL_COMPONENTS LinguistTools Test)
if(UNIX AND NOT APPLE)
  list(APPEND QT_OPTIONAL_COMPONENTS DBus)
endif()

find_package(Qt${QT_VERSION_MAJOR} ${QT_MIN_VERSION} COMPONENTS ${QT_COMPONENTS} REQUIRED OPTIONAL_COMPONENTS ${QT_OPTIONAL_COMPONENTS})

if(Qt${QT_VERSION_MAJOR}DBus_FOUND)
  set(DBUS_FOUND ON)
endif()

if(X11_FOUND)

  find_path(QPA_QPLATFORMNATIVEINTERFACE_H qpa/qplatformnativeinterface.h PATHS ${Qt${QT_VERSION_MAJOR}Gui_INCLUDE_DIRS} ${Qt${QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS})
  if(NOT QPA_QPLATFORMNATIVEINTERFACE_H)
    find_path(QPA_QPLATFORMNATIVEINTERFACE_H ${Qt${QT_VERSION_MAJOR}Gui_VERSION}/QtGui/qpa/qplatformnativeinterface.h PATHS ${Qt${QT_VERSION_MAJOR}Gui_INCLUDE_DIRS} ${Qt${QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS})
  endif()
  if(QPA_QPLATFORMNATIVEINTERFACE_H)
    set(HAVE_QPA_QPLATFORMNATIVEINTERFACE_H ON)
    message(STATUS "Have qpa/qplatformnativeinterface.h header.")
  else()
    message(STATUS "Missing qpa/qplatformnativeinterface.h header.")
  endif()

  # Check for QX11Application (Qt 6 compiled with XCB).
  set(CMAKE_REQUIRED_FLAGS "-std=c++17")
  set(CMAKE_REQUIRED_LIBRARIES Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)
  check_cxx_source_compiles("
    #include <QGuiApplication>
    int main() {
      (void)qApp->nativeInterface<QNativeInterface::QX11Application>();
      return 0;
    }
    "
    HAVE_QX11APPLICATION
  )
  unset(CMAKE_REQUIRED_FLAGS)
  unset(CMAKE_REQUIRED_LIBRARIES)

endif()

# SingleApplication
set(KDSINGLEAPPLICATION_NAME "KDSingleApplication-qt${QT_VERSION_MAJOR}")
find_package(${KDSINGLEAPPLICATION_NAME} 1.1.0)
if(TARGET KDAB::kdsingleapplication)
  set(KDSINGLEAPPLICATION_VERSION "${KDSingleApplication-qt6_VERSION}")
  message(STATUS "Using system KDSingleApplication (Version ${KDSINGLEAPPLICATION_VERSION})")
  set(SINGLEAPPLICATION_LIBRARIES KDAB::kdsingleapplication)
else()
  message(STATUS "Using 3rdparty KDSingleApplication")
  add_subdirectory(3rdparty/kdsingleapplication)
  set(SINGLEAPPLICATION_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/kdsingleapplication/KDSingleApplication/src)
  set(SINGLEAPPLICATION_LIBRARIES kdsingleapplication)
  add_definitions(-DKDSINGLEAPPLICATION_STATIC_BUILD)
endif()

if(APPLE)
  find_library(SPARKLE Sparkle)
  #find_package(SPMediaKeyTap REQUIRED)
endif()

if(WIN32)
  find_package(getopt-win REQUIRED)
endif()

if(APPLE OR WIN32)
  find_package(qtsparkle-qt${QT_VERSION_MAJOR})
  if(TARGET "qtsparkle-qt${QT_VERSION_MAJOR}::qtsparkle")
    set(QTSPARKLE_FOUND ON)
  endif()
endif()

if(UNIX AND NOT APPLE)
  optional_component(ALSA ON "ALSA integration"
    DEPENDS "alsa" ALSA_FOUND
  )
  optional_component(PULSE ON "PulseAudio integration"
    DEPENDS "libpulse" LIBPULSE_FOUND
  )
  optional_component(DBUS ON "D-Bus support"
    DEPENDS "Qt D-Bus" DBUS_FOUND
  )
  optional_component(MPRIS2 ON "MPRIS2 D-Bus Interface"
    DEPENDS "D-Bus support" HAVE_DBUS
  )
endif()

optional_component(SONGFINGERPRINTING ON "Song fingerprinting and tracking"
  DEPENDS "chromaprint" CHROMAPRINT_FOUND
)

optional_component(MUSICBRAINZ ON "MusicBrainz integration"
  DEPENDS "chromaprint" CHROMAPRINT_FOUND
)

if(UNIX AND NOT APPLE)
  optional_component(X11_GLOBALSHORTCUTS ON "X11 global shortcuts"
    DEPENDS "X11" X11_FOUND
    DEPENDS "QX11Application" HAVE_QX11APPLICATION
  )
  optional_component(KGLOBALACCEL_GLOBALSHORTCUTS ON "KGlobalAccel global shortcuts"
    DEPENDS "D-Bus support" HAVE_DBUS
  )
  optional_component(UDISKS2 ON "Devices: UDisks2 backend"
    DEPENDS "D-Bus support" HAVE_DBUS
  )
endif()

if(NOT APPLE)
  optional_component(GIO ON "Devices: GIO device backend"
    DEPENDS "libgio" GIO_FOUND
  )
  if(UNIX)
    optional_component(GIO_UNIX ON "Devices: GIO device backend (Unix support)"
      DEPENDS "libgio-unix" GIO_UNIX_FOUND
    )
  endif()
endif()

optional_component(AUDIOCD ON "Devices: Audio CD support"
  DEPENDS "libcdio" LIBCDIO_FOUND
)

optional_component(MTP ON "Devices: MTP support"
  DEPENDS "libmtp" LIBMTP_FOUND
)

optional_component(GPOD ON "Devices: iPod classic support"
  DEPENDS "libgpod" LIBGPOD_FOUND
  DEPENDS "gdk-pixbuf" GDK_PIXBUF_FOUND
)

optional_component(TRANSLATIONS ON "Translations"
  DEPENDS "Qt LinguistTools" Qt${QT_VERSION_MAJOR}LinguistTools_FOUND
)

optional_component(SUBSONIC ON "Streaming: Subsonic")
optional_component(TIDAL ON "Streaming: Tidal")
optional_component(SPOTIFY ON "Streaming: Spotify")
optional_component(QOBUZ ON "Streaming: Qobuz")

optional_component(MOODBAR ON "Moodbar"
  DEPENDS "fftw3" FFTW3_FOUND
)

optional_component(EBUR128 ON "EBU R 128 loudness normalization"
  DEPENDS "libebur128" LIBEBUR128_FOUND
)

if(APPLE)
  optional_component(SPARKLE ON "Sparkle integration"
    DEPENDS "Sparkle" SPARKLE
  )
endif()

if(APPLE OR WIN32)
  optional_component(QTSPARKLE ON "QtSparkle integration"
    DEPENDS "QtSparkle" QTSPARKLE_FOUND
  )
endif()

if(HAVE_SONGFINGERPRINTING OR HAVE_MUSICBRAINZ)
  set(HAVE_CHROMAPRINT ON)
endif()

if(HAVE_X11_GLOBALSHORTCUTS OR HAVE_KGLOBALACCEL_GLOBALSHORTCUTS OR APPLE OR WIN32)
  set(HAVE_GLOBALSHORTCUTS ON)
endif()

if(NOT CMAKE_CROSSCOMPILING)
  # Check that we have Qt with sqlite driver
  set(CMAKE_REQUIRED_FLAGS "-std=c++17")
  set(CMAKE_REQUIRED_LIBRARIES Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql)
  check_cxx_source_runs("
    #include <QCoreApplication>
    #include <QSqlDatabase>
    #include <QSqlQuery>
    int main(int argc, char *argv[]) {
      QCoreApplication app(argc, argv);
      QSqlDatabase db = QSqlDatabase::addDatabase(\"QSQLITE\");
      db.setDatabaseName(\":memory:\");
      if (!db.open()) { return 1; }
      QSqlQuery q(db);
      q.prepare(\"CREATE TABLE test (test TEXT);\");
      if (!q.exec()) return 1;
    }
    "
    QT_SQLITE_TEST
  )
endif()

add_executable(strawberry)

if(APPLE)
  set_target_properties(strawberry PROPERTIES MACOSX_BUNDLE TRUE)
  set_target_properties(strawberry PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_BINARY_DIR}/dist/macos/Info.plist")
endif()

if(WIN32 AND NOT ENABLE_WIN32_CONSOLE)
  set_target_properties(strawberry PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

set(SOURCES
  src/main/main.cpp
  src/main/mainwindow.cpp
  src/main/application.cpp
  src/main/metatypes.cpp
  src/main/translations.cpp
)

set(HEADERS
  src/main/mainwindow.h
  src/main/application.h
)

set(UI
  src/main/mainwindow.ui
)

qt_wrap_cpp(SOURCES ${HEADERS})
qt_wrap_ui(SOURCES ${UI})
qt_add_resources(SOURCES data/data.qrc data/icons.qrc)

target_sources(strawberry PRIVATE ${SOURCES})

if(WIN32)
  target_sources(strawberry PRIVATE windres.rc)
endif()

add_subdirectory(src)
add_subdirectory(dist)

if(TARGET GTest::gtest AND TARGET GTest::gmock AND Qt${QT_VERSION_MAJOR}Test_FOUND)
  add_subdirectory(tests)
endif()

if(LINUX AND LSB_RELEASE_EXEC AND DPKG_BUILDPACKAGE)
  add_subdirectory(debian)
endif()

if(HAVE_TRANSLATIONS)
  qt_add_lupdate(strawberry TS_FILES "${CMAKE_SOURCE_DIR}/src/translations/strawberry_en_US.ts" OPTIONS -locations none -no-ui-lines -no-obsolete)
  file(GLOB_RECURSE ts_files ${CMAKE_SOURCE_DIR}/src/translations/*.ts)
  set_source_files_properties(${ts_files} PROPERTIES OUTPUT_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/data")
  qt_add_lrelease(strawberry TS_FILES ${ts_files} QM_FILES_OUTPUT_VARIABLE INSTALL_TRANSLATIONS_FILES)
  if(NOT INSTALL_TRANSLATIONS)
    qt_add_resources(strawberry "translations" PREFIX "/i18n" BASE "${CMAKE_CURRENT_BINARY_DIR}/data" FILES "${INSTALL_TRANSLATIONS_FILES}")
  endif()
endif()

target_include_directories(strawberry PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

if(SINGLEAPPLICATION_INCLUDE_DIRS)
  target_include_directories(strawberry SYSTEM PRIVATE ${SINGLEAPPLICATION_INCLUDE_DIRS})
endif()

# if(APPLE)
#   target_link_libraries(strawberry PRIVATE
#     "-framework Foundation"
#     "-framework AppKit"
#     "-framework Carbon"
#     "-framework CoreAudio"
#     "-framework DiskArbitration"
#     "-framework IOKit"
#     "-framework ScriptingBridge"
#     SPMediaKeyTap
#   )
# endif()

target_link_libraries(strawberry PRIVATE
  ${CMAKE_THREAD_LIBS_INIT}
  $<$<BOOL:${HAVE_BACKTRACE}>:${Backtrace_LIBRARIES}>
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
  $<$<BOOL:${HAVE_DBUS}>:Qt${QT_VERSION_MAJOR}::DBus>
  ICU::uc
  ICU::i18n
  $<$<BOOL:${HAVE_ALSA}>:ALSA::ALSA>
  $<$<BOOL:${HAVE_PULSE}>:PkgConfig::LIBPULSE>
  $<$<BOOL:${HAVE_CHROMAPRINT}>:PkgConfig::CHROMAPRINT>
  $<$<BOOL:${HAVE_MOODBAR}>:PkgConfig::FFTW3>
  $<$<BOOL:${HAVE_EBUR128}>:PkgConfig::LIBEBUR128>
  $<$<BOOL:${HAVE_X11_GLOBALSHORTCUTS}>:X11::X11_xcb>
  $<$<BOOL:${HAVE_GIO}>:PkgConfig::GIO>
  $<$<BOOL:${HAVE_GIO_UNIX}>:PkgConfig::GIO_UNIX>
  $<$<BOOL:${HAVE_AUDIOCD}>:PkgConfig::LIBCDIO>
  $<$<BOOL:${HAVE_MTP}>:PkgConfig::LIBMTP>
  $<$<BOOL:${HAVE_GPOD}>:PkgConfig::LIBGPOD PkgConfig::GDK_PIXBUF>
  $<$<BOOL:${HAVE_QTSPARKLE}>:qtsparkle-qt${QT_VERSION_MAJOR}::qtsparkle>
  $<$<BOOL:${WIN32}>:dsound dwmapi getopt-win::getopt>
  $<$<BOOL:${MSVC}>:WindowsApp>
  ${SINGLEAPPLICATION_LIBRARIES}
  $<$<BOOL:${HAVE_QTSPARKLE}>:PkgConfig::QTSPARKLE>
  strawberry_core
  strawberry_utilities
  strawberry_mimedata
  strawberry_osd
  strawberry_tagreader
  strawberry_widgets
  strawberry_engine
  strawberry_lyrics
  strawberry_filterparser
  strawberry_analyzer
  strawberry_transcoder
  strawberry_musicbrainz
  strawberry_collection
  strawberry_playlist
  strawberry_playlistparsers
  strawberry_equalizer
  strawberry_edittagdialog
  strawberry_smartplaylists
  strawberry_fileview
  strawberry_transcoder
  strawberry_organize
  strawberry_context
  strawberry_moodbar
  strawberry_scrobbler
  strawberry_queue
  strawberry_radios
  strawberry_device
  strawberry_settings
  strawberry_providers
  strawberry_player
  strawberry_songloader
  strawberry_systemtrayicon
)

if(APPLE)
  target_link_libraries(strawberry_lib PUBLIC
    "-framework Foundation"
    "-framework AppKit"
    "-framework Carbon"
    "-framework CoreAudio"
    "-framework DiskArbitration"
    "-framework IOKit"
    "-framework ScriptingBridge"
  )
  if(HAVE_SPARKLE)
    target_include_directories(strawberry_lib SYSTEM PRIVATE ${SPARKLE}/Headers)
    target_link_libraries(strawberry_lib PRIVATE ${SPARKLE})
  endif()

if(HAVE_MPRIS2)
  target_link_libraries(strawberry PRIVATE strawberry_mpris2)
endif()

if(HAVE_GLOBALSHORTCUTS)
  target_link_libraries(strawberry PRIVATE strawberry_globalshortcuts)
endif()

if(APPLE)
  target_link_libraries(strawberry PRIVATE strawberry_macstartup)
endif()

if(NOT APPLE)
  install(TARGETS strawberry RUNTIME DESTINATION bin)
endif()

if(HAVE_TRANSLATIONS AND INSTALL_TRANSLATIONS AND INSTALL_TRANSLATIONS_FILES)
  install(FILES ${INSTALL_TRANSLATIONS_FILES} DESTINATION share/strawberry/translations)
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)
add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

optional_component_summary_show()

if(NOT CMAKE_CROSSCOMPILING AND NOT QT_SQLITE_TEST)
  message(WARNING "The Qt sqlite driver test failed.")
endif()
