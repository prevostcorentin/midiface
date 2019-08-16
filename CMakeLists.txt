cmake_minimum_required(VERSION 3.14)
project (midiface VERSION 0.0.1 DESCRIPTION "Midi interface")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library (midiface SHARED
             sources/errutils.c
             sources/memutils.c
             sources/midifile.c)

set_target_properties (midiface PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties (midiface PROPERTIES SOVERSION 1)
set_target_properties (midiface PROPERTIES PUBLIC_HEADER include/midiface.h)
target_include_directories (midiface PRIVATE .)

add_executable (dump-midi-file examples/sources/dump-midi-file.c)
target_link_libraries (dump-midi-file midiface)
target_include_directories (dump-midi-file PRIVATE .)

include (GNUInstallDirs)

install (TARGETS midiface
         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
         PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})