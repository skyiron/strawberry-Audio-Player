set(FILEVIEW_SOURCES
  fileview.cpp
  fileviewlist.cpp
)

set(FILEVIEW_HEADERS
  fileview.h
  fileviewlist.h
)

set(FILEVIEW_UI
  fileview.ui
)

qt_wrap_cpp(FILEVIEW_SOURCES ${FILEVIEW_HEADERS})
qt_wrap_ui(FILEVIEW_SOURCES ${FILEVIEW_UI})

add_library(strawberry_fileview STATIC ${FILEVIEW_SOURCES})

target_include_directories(strawberry_fileview PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_fileview PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_mimedata
  strawberry_dialogs
  strawberry_organize
)
