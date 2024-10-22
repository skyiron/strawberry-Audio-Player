set(SOURCES
  filterparser.cpp
  filtertree.cpp
  filtertreeand.cpp
  filtertreecolumnterm.cpp
  filtertreenop.cpp
  filtertreenot.cpp
  filtertreeor.cpp
  filtertreeterm.cpp
  filterparserfloateqcomparator.cpp
  filterparserfloatgecomparator.cpp
  filterparserfloatgtcomparator.cpp
  filterparserfloatlecomparator.cpp
  filterparserfloatltcomparator.cpp
  filterparserfloatnecomparator.cpp
  filterparserint64eqcomparator.cpp
  filterparserint64gecomparator.cpp
  filterparserint64gtcomparator.cpp
  filterparserint64lecomparator.cpp
  filterparserint64ltcomparator.cpp
  filterparserint64necomparator.cpp
  filterparserinteqcomparator.cpp
  filterparserintgecomparator.cpp
  filterparserintgtcomparator.cpp
  filterparserintlecomparator.cpp
  filterparserintltcomparator.cpp
  filterparserintnecomparator.cpp
  filterparsersearchtermcomparator.cpp
  filterparsertextcontainscomparator.cpp
  filterparsertexteqcomparator.cpp
  filterparsertextnecomparator.cpp
  filterparseruinteqcomparator.cpp
  filterparseruintgecomparator.cpp
  filterparseruintgtcomparator.cpp
  filterparseruintlecomparator.cpp
  filterparseruintltcomparator.cpp
  filterparseruintnecomparator.cpp
)

add_library(strawberry_filterparser STATIC ${SOURCES})

target_include_directories(strawberry_filterparser PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_filterparser PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)
