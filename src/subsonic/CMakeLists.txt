set(SUBSONIC_SOURCES
  subsonicservice.cpp
  subsonicurlhandler.cpp
  subsonicbaserequest.cpp
  subsonicrequest.cpp
  subsonicscrobblerequest.cpp
)

set(SUBSONIC_HEADERS
  subsonicservice.h
  subsonicurlhandler.h
  subsonicbaserequest.h
  subsonicrequest.h
  subsonicscrobblerequest.h
)

qt_wrap_cpp(SUBSONIC_SOURCES ${SUBSONIC_HEADERS})

add_library(strawberry_subsonic STATIC ${SUBSONIC_SOURCES})

target_include_directories(strawberry_subsonic PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_subsonic PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
)
