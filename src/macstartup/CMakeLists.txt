set(MACSTARTUP_SOURCES mac_startup.mm)

add_library(strawberry_macstartup STATIC ${MACSTARTUP_SOURCES})

target_include_directories(strawberry_macstartup PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_macstartup PRIVATE
  "-framework Foundation"
  "-framework AppKit"
  "-framework IOKit"
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  SPMediaKeyTap
  strawberry_utilities
  strawberry_core
  strawberry_globalshortcuts
)
