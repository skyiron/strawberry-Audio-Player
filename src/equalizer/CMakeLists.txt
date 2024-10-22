set(EQUALIZER_SOURCES
  equalizer.cpp
  equalizerslider.cpp
)

set(EQUALIZER_HEADERS
  equalizer.h
  equalizerslider.h
)

set(EQUALIZER_UI
  equalizer.ui
  equalizerslider.ui
)

qt_wrap_cpp(EQUALIZER_SOURCES ${EQUALIZER_HEADERS})
qt_wrap_ui(EQUALIZER_SOURCES ${EQUALIZER_UI})

add_library(strawberry_equalizer STATIC ${EQUALIZER_SOURCES})

target_include_directories(strawberry_equalizer PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_equalizer PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
  strawberry_widgets
)
