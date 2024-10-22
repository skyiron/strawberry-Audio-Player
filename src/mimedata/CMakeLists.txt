set(MIMEDATA_SOURCES
  mimedata.cpp
  songmimedata.cpp
)

set(MIMEDATA_HEADERS
  mimedata.h
  songmimedata.h
)

qt_wrap_cpp(MIMEDATA_SOURCES ${MIMEDATA_HEADERS})

add_library(strawberry_mimedata STATIC ${MIMEDATA_SOURCES})

target_include_directories(strawberry_mimedata PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_mimedata PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  strawberry_core
  strawberry_collection
)
