set(ENGINE_SOURCES
  enginebase.cpp
  enginedevice.cpp
  devicefinders.cpp
  devicefinder.cpp
  gststartup.cpp
  gstengine.cpp
  gstenginepipeline.cpp
)

set(ENGINE_HEADERS
  enginebase.h
  devicefinders.h
  gststartup.h
  gstengine.h
  gstenginepipeline.h
)

if(HAVE_ALSA)
  list(APPEND ENGINE_SOURCES alsadevicefinder.cpp alsapcmdevicefinder.cpp)
endif()

if(HAVE_PULSE)
  list(APPEND ENGINE_SOURCES pulsedevicefinder.cpp)
endif()

if(MSVC)
  list(APPEND ENGINE_SOURCES uwpdevicefinder.cpp asiodevicefinder.cpp)
endif()

if(HAVE_SONGFINGERPRINTING OR HAVE_MUSICBRAINZ)
  list(APPEND ENGINE_SOURCES chromaprinter.cpp)
endif()

if(HAVE_EBUR128)
  list(APPEND ENGINE_SOURCES ebur128analysis.cpp)
endif()

if(HAVE_MOODBAR)
  list(APPEND ENGINE_SOURCES gstfastspectrumplugin.cpp gstfastspectrum.cpp)
endif()

if(APPLE)
  list(APPEND ENGINE_SOURCES macosdevicefinder.cpp)
endif()

if(WIN32)
  list(APPEND ENGINE_SOURCES directsounddevicefinder.cpp mmdevicefinder.cpp)
endif()

qt_wrap_cpp(ENGINE_SOURCES ${ENGINE_HEADERS})

add_library(strawberry_engine STATIC ${ENGINE_SOURCES})

target_include_directories(strawberry_engine PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_engine PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  $<$<BOOL:${HAVE_ALSA}>:ALSA::ALSA>
  $<$<BOOL:${HAVE_PULSE}>:PkgConfig::LIBPULSE>
  $<$<BOOL:${WIN32}>:dsound>
  $<$<BOOL:${MSVC}>:WindowsApp>
  PkgConfig::GSTREAMER
  PkgConfig::GSTREAMER_BASE
  PkgConfig::GSTREAMER_AUDIO
  PkgConfig::GSTREAMER_APP
  PkgConfig::GSTREAMER_TAG
  PkgConfig::GSTREAMER_PBUTILS
  $<$<BOOL:${HAVE_SONGFINGERPRINTING} OR ${HAVE_MUSICBRAINZ}>:PkgConfig::CHROMAPRINT>
  $<$<BOOL:${HAVE_EBUR128}>:PkgConfig::LIBEBUR128>
  $<$<BOOL:${HAVE_MOODBAR}>:PkgConfig::FFTW3>
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Gui
  strawberry_core
)

if(APPLE)
  target_link_libraries(strawberry_engine PRIVATE
    "-framework CoreAudio"
  )
endif()
