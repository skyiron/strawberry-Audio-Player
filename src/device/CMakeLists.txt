set(DEVICE_SOURCES
  connecteddevice.cpp
  devicedatabasebackend.cpp
  devicelister.cpp
  devicemanager.cpp
  devicestatefiltermodel.cpp
  filesystemdevice.cpp
  deviceviewcontainer.cpp
  deviceview.cpp
  deviceproperties.cpp
  deviceinfo.cpp
)

set(DEVICE_HEADERS
  connecteddevice.h
  devicedatabasebackend.h
  devicelister.h
  devicemanager.h
  devicestatefiltermodel.h
  filesystemdevice.h
  deviceviewcontainer.h
  deviceview.h
  deviceproperties.h
)

set(DEVICE_UI
  deviceproperties.ui
  deviceviewcontainer.ui
)

if(APPLE)
  list(APPEND DEVICE_SOURCES macosdevicelister.mm)
  list(APPEND DEVICE_HEADERS macosdevicelister.h)
endif()

if(UNIX)
  list(APPEND DEVICE_SOURCES giolister.cpp)
  list(APPEND DEVICE_HEADERS giolister.h)
endif()

if(HAVE_UDISKS2)
  list(APPEND DEVICE_SOURCES udisks2lister.cpp)
  list(APPEND DEVICE_HEADERS udisks2lister.h)
  set_source_files_properties(org.freedesktop.DBus.ObjectManager.xml PROPERTIES NO_NAMESPACE objectmanager INCLUDE includes/dbus_metatypes.h)
  set_source_files_properties(org.freedesktop.UDisks2.Filesystem.xml PROPERTIES NO_NAMESPACE udisks2filesystem INCLUDE includes/dbus_metatypes.h)
  set_source_files_properties(org.freedesktop.UDisks2.Block.xml PROPERTIES NO_NAMESPACE udisks2block INCLUDE includes/dbus_metatypes.h)
  set_source_files_properties(org.freedesktop.UDisks2.Drive.xml PROPERTIES NO_NAMESPACE udisks2drive INCLUDE includes/dbus_metatypes.h)
  set_source_files_properties(org.freedesktop.UDisks2.Job.xml PROPERTIES NO_NAMESPACE udisks2job INCLUDE includes/dbus_metatypes.h)
  qt_add_dbus_interface(DEVICE_SOURCES org.freedesktop.DBus.ObjectManager.xml objectmanager)
  qt_add_dbus_interface(DEVICE_SOURCES org.freedesktop.UDisks2.Filesystem.xml udisks2filesystem)
  qt_add_dbus_interface(DEVICE_SOURCES org.freedesktop.UDisks2.Block.xml udisks2block)
  qt_add_dbus_interface(DEVICE_SOURCES org.freedesktop.UDisks2.Drive.xml udisks2drive)
  qt_add_dbus_interface(DEVICE_SOURCES org.freedesktop.UDisks2.Job.xml udisks2job)
endif()

if(HAVE_MTP)
  list(APPEND DEVICE_SOURCES mtpconnection.cpp mtpdevice.cpp mtploader.cpp)
  list(APPEND DEVICE_HEADERS mtpconnection.h mtpdevice.h mtploader.h)
endif()

if(HAVE_AUDIOCD)
  list(APPEND DEVICE_SOURCES cddadevice.cpp cddalister.cpp cddasongloader.cpp)
  list(APPEND DEVICE_HEADERS cddadevice.h cddalister.h cddasongloader.h)
endif()

if(HAVE_GPOD)
  list(APPEND DEVICE_SOURCES gpoddevice.cpp gpodloader.cpp)
  list(APPEND DEVICE_HEADERS gpoddevice.h gpodloader.h)
endif()

qt_wrap_cpp(DEVICE_SOURCES ${DEVICE_HEADERS})
qt_wrap_ui(DEVICE_SOURCES ${DEVICE_UI})

add_library(strawberry_device STATIC ${DEVICE_SOURCES})

target_include_directories(strawberry_device PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_device PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  PkgConfig::GSTREAMER
  PkgConfig::GSTREAMER_BASE
  PkgConfig::GSTREAMER_AUDIO
  PkgConfig::GSTREAMER_APP
  PkgConfig::GSTREAMER_TAG
  PkgConfig::GSTREAMER_PBUTILS
  $<$<BOOL:${HAVE_GIO}>:PkgConfig::GIO>
  $<$<BOOL:${HAVE_GIO_UNIX}>:PkgConfig::GIO_UNIX>
  $<$<BOOL:${HAVE_AUDIOCD}>:PkgConfig::LIBCDIO>
  $<$<BOOL:${HAVE_MTP}>:PkgConfig::LIBMTP>
  $<$<BOOL:${HAVE_GPOD}>:PkgConfig::LIBGPOD PkgConfig::GDK_PIXBUF>
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  $<$<BOOL:${HAVE_DBUS}>:Qt${QT_VERSION_MAJOR}::DBus>
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_collection
  strawberry_widgets
  strawberry_musicbrainz
)

if(APPLE)
  target_link_libraries(strawberry_device PRIVATE
    "-framework IOKit"
    "-framework DiskArbitration"
  )
endif()
