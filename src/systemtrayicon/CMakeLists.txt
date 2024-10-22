set(SYSTEMTRAYICON_SOURCES systemtrayicon.cpp)

if(APPLE)
  list(APPEND SYSTEMTRAYICON_SOURCES macsystemtrayicon.mm)
  list(APPEND SYSTEMTRAYICON_HEADERS macsystemtrayicon.h)
else()
  list(APPEND SYSTEMTRAYICON_SOURCES qtsystemtrayicon.cpp)
  list(APPEND SYSTEMTRAYICON_HEADERS qtsystemtrayicon.h)
endif()

qt_wrap_cpp(SYSTEMTRAYICON_SOURCES ${SYSTEMTRAYICON_HEADERS})

add_library(strawberry_systemtrayicon STATIC ${SYSTEMTRAYICON_SOURCES})

target_include_directories(strawberry_systemtrayicon PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_systemtrayicon PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
)
