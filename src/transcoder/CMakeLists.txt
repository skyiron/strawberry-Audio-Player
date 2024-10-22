set(TRANSCODER_SOURCES
  transcoder.cpp
  transcoderoptionsinterface.cpp
  transcodedialog.cpp
  transcoderoptionsdialog.cpp
  transcoderoptionsflac.cpp
  transcoderoptionswavpack.cpp
  transcoderoptionsvorbis.cpp
  transcoderoptionsopus.cpp
  transcoderoptionsspeex.cpp
  transcoderoptionsaac.cpp
  transcoderoptionsasf.cpp
  transcoderoptionsmp3.cpp
)

set(TRANSCODER_HEADERS
  transcoder.h
  transcodedialog.h
  transcoderoptionsdialog.h
  transcoderoptionsinterface.h
  transcoderoptionsflac.h
  transcoderoptionswavpack.h
  transcoderoptionsvorbis.h
  transcoderoptionsopus.h
  transcoderoptionsspeex.h
  transcoderoptionsaac.h
  transcoderoptionsasf.h
  transcoderoptionsmp3.h
)

set(TRANSCODER_UI
  transcodedialog.ui
  transcodelogdialog.ui
  transcoderoptionsaac.ui
  transcoderoptionsdialog.ui
  transcoderoptionsflac.ui
  transcoderoptionswavpack.ui
  transcoderoptionsvorbis.ui
  transcoderoptionsopus.ui
  transcoderoptionsspeex.ui
  transcoderoptionsasf.ui
  transcoderoptionsmp3.ui
)

qt_wrap_cpp(TRANSCODER_SOURCES ${TRANSCODER_HEADERS})
qt_wrap_ui(TRANSCODER_SOURCES ${TRANSCODER_UI})

add_library(strawberry_transcoder STATIC ${TRANSCODER_SOURCES})

target_include_directories(strawberry_transcoder PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_transcoder PRIVATE
  PkgConfig::GLIB
  PkgConfig::GOBJECT
  PkgConfig::GSTREAMER
  PkgConfig::GSTREAMER_BASE
  PkgConfig::GSTREAMER_AUDIO
  PkgConfig::GSTREAMER_APP
  PkgConfig::GSTREAMER_TAG
  PkgConfig::GSTREAMER_PBUTILS
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
  strawberry_utilities
)
