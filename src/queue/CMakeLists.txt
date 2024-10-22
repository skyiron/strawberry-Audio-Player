set(QUEUE_SOURCES
  queue.cpp
  queueview.cpp
)

set(QUEUE_HEADERS
  queue.h
  queueview.h
)

set(QUEUE_UI
  queueview.ui
)

qt_wrap_cpp(QUEUE_SOURCES ${QUEUE_HEADERS})
qt_wrap_ui(QUEUE_SOURCES ${QUEUE_UI})

add_library(strawberry_queue STATIC ${QUEUE_SOURCES})

target_include_directories(strawberry_queue PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_queue PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
  strawberry_playlist
)
