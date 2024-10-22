set(CONTEXT_SOURCES
  contextview.cpp
  contextalbum.cpp
)

set(CONTEXT_HEADERS
  contextview.h
  contextalbum.h
)

qt_wrap_cpp(CONTEXT_SOURCES ${CONTEXT_HEADERS})

add_library(strawberry_context STATIC ${CONTEXT_SOURCES})

target_include_directories(strawberry_context PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_context PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_collection
  strawberry_covermanager
  strawberry_lyrics
  strawberry_widgets
)
