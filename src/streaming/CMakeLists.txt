set(STREAMING_SOURCES
  streamingservices.cpp
  streamingservice.cpp
  streamplaylistitem.cpp
  streamingsearchview.cpp
  streamingsearchmodel.cpp
  streamingsearchsortmodel.cpp
  streamingsearchitemdelegate.cpp
  streamingsongsview.cpp
  streamingtabsview.cpp
  streamingcollectionview.cpp
  streamingcollectionviewcontainer.cpp
  streamingsearchview.cpp
  streamsongmimedata.cpp
)

set(STREAMING_HEADERS
  streamingservices.h
  streamingservice.h
  streamsongmimedata.h
  streamingsearchmodel.h
  streamingsearchsortmodel.h
  streamingsearchitemdelegate.h
  streamingsearchview.h
  streamingsongsview.h
  streamingtabsview.h
  streamingcollectionview.h
  streamingcollectionviewcontainer.h
)

set(STREAMING_UI
  streamingtabsview.ui
  streamingcollectionviewcontainer.ui
  streamingsearchview.ui
)

qt_wrap_cpp(STREAMING_SOURCES ${STREAMING_HEADERS})
qt_wrap_ui(STREAMING_SOURCES ${STREAMING_UI})

add_library(strawberry_streaming STATIC ${STREAMING_SOURCES})

target_include_directories(strawberry_streaming PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_streaming PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
  strawberry_mimedata
  strawberry_collection
  strawberry_covermanager
)
