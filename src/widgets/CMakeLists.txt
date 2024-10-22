set(WIDGETS_SOURCES
  autoexpandingtreeview.cpp
  busyindicator.cpp
  clickablelabel.cpp
  fancytabwidget.cpp
  fancytabbar.cpp
  fancytabdata.cpp
  favoritewidget.cpp
  forcescrollperpixel.cpp
  freespacebar.cpp
  groupediconview.cpp
  lineedit.cpp
  linetextedit.cpp
  multiloadingindicator.cpp
  playingwidget.cpp
  renametablineedit.cpp
  sliderslider.cpp
  prettyslider.cpp
  volumeslider.cpp
  stickyslider.cpp
  stretchheaderview.cpp
  trackslider.cpp
  tracksliderpopup.cpp
  tracksliderslider.cpp
  loginstatewidget.cpp
  ratingwidget.cpp
  resizabletextedit.cpp
)

set(WIDGETS_HEADERS
  autoexpandingtreeview.h
  busyindicator.h
  clickablelabel.h
  fancytabwidget.h
  fancytabbar.h
  fancytabdata.h
  favoritewidget.h
  freespacebar.h
  groupediconview.h
  lineedit.h
  linetextedit.h
  multiloadingindicator.h
  playingwidget.h
  renametablineedit.h
  sliderslider.h
  prettyslider.h
  volumeslider.h
  stickyslider.h
  stretchheaderview.h
  trackslider.h
  tracksliderpopup.h
  tracksliderslider.h
  loginstatewidget.h
  searchfield.h
  ratingwidget.h
  forcescrollperpixel.h
  resizabletextedit.h
)

set(WIDGETS_UI
  trackslider.ui
  loginstatewidget.ui
)

if(APPLE)
  list(APPEND WIDGETS_SOURCES searchfield_mac.mm)
else()
  list(APPEND WIDGETS_SOURCES searchfield_qt.cpp searchfield_qt_private.cpp)
  list(APPEND WIDGETS_HEADERS searchfield_qt_private.h)
endif()

qt_wrap_cpp(WIDGETS_SOURCES ${WIDGETS_HEADERS})
qt_wrap_ui(WIDGETS_SOURCES ${WIDGETS_UI})

add_library(strawberry_widgets STATIC ${WIDGETS_SOURCES})

target_include_directories(strawberry_widgets PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_widgets PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_utilities
  strawberry_core
  strawberry_mimedata
  strawberry_covermanager
)
