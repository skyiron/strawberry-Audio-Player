set(PROVIDERS_SOURCES
  musixmatchprovider.cpp
)

add_library(strawberry_providers STATIC ${PROVIDERS_SOURCES})

target_include_directories(strawberry_providers PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_providers PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
)
