set(MOODBAR_SOURCES
  moodbarbuilder.cpp
  moodbarcontroller.cpp
  moodbaritemdelegate.cpp
  moodbarloader.cpp
  moodbarpipeline.cpp
  moodbarproxystyle.cpp
  moodbarrenderer.cpp
)

set(MOODBAR_HEADERS
  moodbarcontroller.h
  moodbaritemdelegate.h
  moodbarloader.h
  moodbarpipeline.h
  moodbarproxystyle.h
)

qt_wrap_cpp(MOODBAR_SOURCES ${MOODBAR_HEADERS})

add_library(strawberry_moodbar STATIC ${MOODBAR_SOURCES})

target_include_directories(strawberry_moodbar PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_moodbar PRIVATE
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
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
)
