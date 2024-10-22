set(ANALYZER_SOURCES
  fht.cpp
  analyzerbase.cpp
  analyzercontainer.cpp
  blockanalyzer.cpp
  boomanalyzer.cpp
  turbineanalyzer.cpp
  sonogramanalyzer.cpp
  waverubberanalyzer.cpp
  rainbowanalyzer.cpp
)

set(ANALYZER_HEADERS
  analyzerbase.h
  analyzercontainer.h
  blockanalyzer.h
  boomanalyzer.h
  turbineanalyzer.h
  sonogramanalyzer.h
  waverubberanalyzer.h
  rainbowanalyzer.h
)

qt_wrap_cpp(ANALYZER_SOURCES ${ANALYZER_HEADERS})

add_library(strawberry_analyzer STATIC ${ANALYZER_SOURCES})

target_include_directories(strawberry_analyzer PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_analyzer PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
  strawberry_engine
)
