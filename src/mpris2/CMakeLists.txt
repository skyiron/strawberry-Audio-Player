set(MPRIS2_SOURCES
  mpris2.cpp
)

set(MPRIS2_HEADERS
  mpris2.h
)

qt_wrap_cpp(MPRIS2_SOURCES ${MPRIS2_HEADERS})

qt_add_dbus_adaptor(MPRIS2_SOURCES org.mpris.MediaPlayer2.xml mpris2.h mpris::Mpris2 mpris2_root Mpris2Root)
qt_add_dbus_adaptor(MPRIS2_SOURCES org.mpris.MediaPlayer2.Player.xml mpris2.h mpris::Mpris2 mpris2_player Mpris2Player)
qt_add_dbus_adaptor(MPRIS2_SOURCES org.mpris.MediaPlayer2.TrackList.xml mpris2.h mpris::Mpris2 mpris2_tracklist Mpris2TrackList)
qt_add_dbus_adaptor(MPRIS2_SOURCES org.mpris.MediaPlayer2.Playlists.xml mpris2.h mpris::Mpris2 mpris2_playlists Mpris2Playlists)

add_library(strawberry_mpris2 STATIC ${MPRIS2_SOURCES})

target_include_directories(strawberry_mpris2 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

target_link_libraries(strawberry_mpris2 PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::DBus
  Qt${QT_VERSION_MAJOR}::Widgets
  strawberry_core
  strawberry_engine
  strawberry_player
)
