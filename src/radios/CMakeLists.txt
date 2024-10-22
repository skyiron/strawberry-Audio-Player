set(RADIOS_SOURCES
  radioservices.cpp
  radiobackend.cpp
  radiomodel.cpp
  radioview.cpp
  radioviewcontainer.cpp
  radioservice.cpp
  radioplaylistitem.cpp
  radiochannel.cpp
  somafmservice.cpp
  radioparadiseservice.cpp
  radiomimedata.cpp
)

set(RADIOS_HEADERS
  radioservices.h
  radiobackend.h
  radiomodel.h
  radioview.h
  radioviewcontainer.h
  radioservice.h
  radiomimedata.h
  somafmservice.h
  radioparadiseservice.h
)

set(RADIOS_UI
  radioviewcontainer.ui
)

qt_wrap_cpp(RADIOS_SOURCES ${RADIOS_HEADERS})
qt_wrap_ui(RADIOS_SOURCES ${RADIOS_UI})

add_library(strawberry_radios STATIC ${RADIOS_SOURCES})

target_include_directories(strawberry_radios PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_radios PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
  strawberry_collection
)
