cmake_minimum_required(VERSION 3.14)
project(midiface VERSION 0.0.1 DESCRIPTION "Virtual MIDI hub")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(midiface SHARED sources/errutils.c
                            sources/logger.c
                            sources/memutils.c
                            sources/midiheader.c
                            sources/midifile.c
                            sources/midistream.c)

set_target_properties (midiface PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties (midiface PROPERTIES SOVERSION 1)
set_target_properties (midiface PROPERTIES PUBLIC_HEADER include/midiface.h)
target_include_directories(midiface PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(midiface-tests tests/sources/tests.c)
target_link_libraries(midiface-tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/lib/lib/libcunit.a
        midiface)
add_custom_command(TARGET midiface-tests PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/files $<TARGET_FILE_DIR:midiface-tests>/tests/files)
target_include_directories(midiface-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        tests/lib/include)

include (GNUInstallDirs)

install (TARGETS midiface
         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
         PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})