set(COLLECTION_SOURCES
  collectionlibrary.cpp
  collectionmodel.cpp
  collectionbackend.cpp
  collectionwatcher.cpp
  collectionview.cpp
  collectionitemdelegate.cpp
  collectionviewcontainer.cpp
  collectiondirectorymodel.cpp
  collectionfilteroptions.cpp
  collectionfilterwidget.cpp
  collectionfilter.cpp
  collectionplaylistitem.cpp
  collectionquery.cpp
  savedgroupingmanager.cpp
  groupbydialog.cpp
  collectiontask.cpp
  collectionmodelupdate.cpp
  collectionitem.cpp
)

set(COLLECTION_HEADERS
  collectionlibrary.h
  collectionmodel.h
  collectionbackend.h
  collectionwatcher.h
  collectionview.h
  collectionitemdelegate.h
  collectionviewcontainer.h
  collectiondirectorymodel.h
  collectionfilterwidget.h
  collectionfilter.h
  savedgroupingmanager.h
  groupbydialog.h
)

set(COLLECTION_UI
  groupbydialog.ui
  collectionfilterwidget.ui
  collectionviewcontainer.ui
  savedgroupingmanager.ui
)

qt_wrap_cpp(COLLECTION_SOURCES ${COLLECTION_HEADERS})
qt_wrap_ui(COLLECTION_SOURCES ${COLLECTION_UI})

add_library(strawberry_collection STATIC ${COLLECTION_SOURCES})

target_include_directories(strawberry_collection PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_collection PRIVATE
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
  strawberry_mimedata
  strawberry_engine
  strawberry_tagreader
  strawberry_covermanager
  strawberry_filterparser
  strawberry_dialogs
  strawberry_edittagdialog
  strawberry_organize
  strawberry_playlistparsers
)
