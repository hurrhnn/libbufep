cmake_minimum_required(VERSION 3.1)
project(libbufep VERSION 0.0.1 LANGUAGES C)

include(GNUInstallDirs)

set(CMAKE_C_STANDARD 99)
option(BUFEP_INSTALL_PKGCONFIG "install pkg-config module." ON)
option(BUFEP_ENABLE_DEBUG "enable bufep debug functions." OFF)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(BUFEP_ENABLE_DEBUG ON)
endif()

add_library(bufep SHARED src/bufep.c src/bufep_pmtud.c include/bufep_pmtud.h src/bufep_socket.c include/bufep_socket.h test/test_socket_server.c src/bufep_private.h src/bufep_debug.c include/bufep_debug.h src/bufep_fletcher.c include/bufep_fletcher.h)
configure_file(${PROJECT_SOURCE_DIR}/include/bufep_config.h.in ${PROJECT_SOURCE_DIR}/include/bufep_config.h)
FILE(GLOB BUFEP_PUBLIC_HEADER "include/*.h")

set_target_properties(bufep
        PROPERTIES SOVERSION
        ${PROJECT_VERSION_MAJOR}
        VERSION
        ${CMAKE_PROJECT_VERSION}
        PUBLIC_HEADER
        "${BUFEP_PUBLIC_HEADER}")

target_include_directories(
        bufep
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/bufep>)

install(TARGETS bufep
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bufep)

if(BUFEP_INSTALL_PKGCONFIG)
    set(prefix ${CMAKE_INSTALL_PREFIX})
    set(exec_prefix ${CMAKE_INSTALL_PREFIX})
    set(libdir ${CMAKE_INSTALL_FULL_LIBDIR})
    set(includedir ${CMAKE_INSTALL_FULL_INCLUDEDIR})
    set(VERSION ${CMAKE_PROJECT_VERSION})

    configure_file(bufep.pc.in bufep.pc)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bufep.pc
            DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig)
endif()

if(NOT BUFEP_DISABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
