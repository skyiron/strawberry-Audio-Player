set(QOBUZ_SOURCES
  qobuzservice.cpp
  qobuzurlhandler.cpp
  qobuzbaserequest.cpp
  qobuzrequest.cpp
  qobuzstreamurlrequest.cpp
  qobuzfavoriterequest.cpp
)

set(QOBUZ_HEADERS
  qobuzservice.h
  qobuzurlhandler.h
  qobuzbaserequest.h
  qobuzrequest.h
  qobuzstreamurlrequest.h
  qobuzfavoriterequest.h
)

qt_wrap_cpp(QOBUZ_SOURCES ${QOBUZ_HEADERS})
qt_wrap_ui(QOBUZ_SOURCES ${QOBUZ_UI})

add_library(strawberry_qobuz STATIC ${QOBUZ_SOURCES})

target_include_directories(strawberry_qobuz PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_qobuz PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_collection
  strawberry_streaming
)
