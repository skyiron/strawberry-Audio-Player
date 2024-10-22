set(SOURCES
  tagreaderclient.cpp
  tagreaderresult.cpp
  tagreaderbase.cpp
  tagreadertaglib.cpp
  tagreadergme.cpp
  tagreaderrequest.cpp
  tagreaderismediafilerequest.cpp
  tagreaderreadfilerequest.cpp
  tagreaderwritefilerequest.cpp
  tagreaderloadcoverdatarequest.cpp
  tagreaderloadcoverimagerequest.cpp
  tagreadersavecoverrequest.cpp
  tagreadersaveplaycountrequest.cpp
  tagreadersaveratingrequest.cpp
  albumcovertagdata.cpp
  savetagcoverdata.cpp
  tagreaderreply.cpp
  tagreaderreadfilereply.cpp
  tagreaderloadcoverdatareply.cpp
  tagreaderloadcoverimagereply.cpp
)

set(HEADERS
  tagreaderclient.h
  tagreaderreply.h
  tagreaderreadfilereply.h
  tagreaderloadcoverdatareply.h
  tagreaderloadcoverimagereply.h
)

qt_wrap_cpp(SOURCES ${HEADERS})

add_library(strawberry_tagreader STATIC ${SOURCES})

target_include_directories(strawberry_tagreader PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_tagreader PRIVATE
  ${TAGLIB_LIBRARIES}
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  strawberry_core
)
