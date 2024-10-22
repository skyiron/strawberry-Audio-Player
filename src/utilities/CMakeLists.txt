set(UTILITIES_SOURCES
  strutils.cpp
  envutils.cpp
  colorutils.cpp
  cryptutils.cpp
  fileutils.cpp
  diskutils.cpp
  imageutils.cpp
  macaddrutils.cpp
  mimeutils.cpp
  randutils.cpp
  threadutils.cpp
  timeutils.cpp
  transliterate.cpp
  xmlutils.cpp
  filemanagerutils.cpp
  coverutils.cpp
  coveroptions.cpp
  screenutils.cpp
  textencodingutils.cpp
)

if(APPLE)
  list(APPEND UTILITIES_SOURCES macosutils.mm)
endif()

if(WIN32)
  list(APPEND UTILITIES_SOURCES scopedwchararray.cpp winutils.cpp)
endif()

add_library(strawberry_utilities STATIC ${UTILITIES_SOURCES})

target_include_directories(strawberry_utilities PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_utilities PRIVATE
  ICU::uc
  ICU::i18n
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  $<$<BOOL:${WIN32}>:dwmapi>
)
