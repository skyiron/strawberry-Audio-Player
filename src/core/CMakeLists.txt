set(CORE_SOURCES
  logging.cpp
  commandlineoptions.cpp
  database.cpp
  memorydatabase.cpp
  sqlquery.cpp
  sqlrow.cpp
  deletefiles.cpp
  filesystemmusicstorage.cpp
  filesystemwatcherinterface.cpp
  mergedproxymodel.cpp
  multisortfilterproxy.cpp
  musicstorage.cpp
  networkaccessmanager.cpp
  threadsafenetworkdiskcache.cpp
  networktimeouts.cpp
  networkproxyfactory.cpp
  qtfslistener.cpp
  settings.cpp
  settingsprovider.cpp
  signalchecker.cpp
  song.cpp
  stylehelper.cpp
  stylesheetloader.cpp
  taskmanager.cpp
  thread.cpp
  urlhandlers.cpp
  urlhandler.cpp
  iconloader.cpp
  standarditemiconloader.cpp
  scopedtransaction.cpp
  localredirectserver.cpp
  temporaryfile.cpp
  enginemetadata.cpp
  platforminterface.cpp
)

set(CORE_HEADERS
  logging.h
  database.h
  memorydatabase.h
  deletefiles.h
  filesystemwatcherinterface.h
  mergedproxymodel.h
  multisortfilterproxy.h
  networkaccessmanager.h
  threadsafenetworkdiskcache.h
  networktimeouts.h
  qtfslistener.h
  settings.h
  taskmanager.h
  thread.h
  urlhandlers.h
  urlhandler.h
  standarditemiconloader.h
  stylesheetloader.h
  localredirectserver.h
)

if(APPLE)
  list(APPEND CORE_SOURCES scoped_nsautorelease_pool.mm)
endif()

if(WIN32)
  list(APPEND CORE_SOURCES windows7thumbbar.cpp)
  list(APPEND CORE_HEADERS windows7thumbbar.h)
endif()

qt_wrap_cpp(CORE_SOURCES ${CORE_HEADERS})

add_library(strawberry_core STATIC ${CORE_SOURCES})

target_include_directories(strawberry_core PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_core PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  PkgConfig::SQLITE
  ${TAGLIB_LIBRARIES}
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  $<$<BOOL:${HAVE_DBUS}>:Qt${QT_VERSION_MAJOR}::DBus>
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  $<$<BOOL:${HAVE_GPOD}>:PkgConfig::LIBGPOD PkgConfig::GDK_PIXBUF>
  $<$<BOOL:${WIN32}>:getopt-win::getopt>
  strawberry_utilities
)
