set(TIDAL_SOURCES
  tidalservice.cpp
  tidalurlhandler.cpp
  tidalbaserequest.cpp
  tidalrequest.cpp
  tidalstreamurlrequest.cpp
  tidalfavoriterequest.cpp
)

set(TIDAL_HEADERS
  tidalservice.h
  tidalurlhandler.h
  tidalbaserequest.h
  tidalrequest.h
  tidalstreamurlrequest.h
  tidalfavoriterequest.h
)

qt_wrap_cpp(TIDAL_SOURCES ${TIDAL_HEADERS})
qt_wrap_ui(TIDAL_SOURCES ${TIDAL_UI})

add_library(strawberry_tidal STATIC ${TIDAL_SOURCES})

target_include_directories(strawberry_tidal PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_tidal PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_streaming
  strawberry_collection
  strawberry_covermanager
)
