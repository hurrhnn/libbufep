cmake_minimum_required(VERSION 3.1)
project(libbufep VERSION 0.0.1 LANGUAGES C)

include(GNUInstallDirs)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_C_STANDARD 99)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
option(BUFEP_INSTALL_PKGCONFIG "install pkg-config module." ON)
option(BUFEP_ENABLE_DEBUG "enable bufep debug functions." OFF)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX ON)
else()
    set(LINUX OFF)
endif()

if(LINUX)
    find_package(LibUUID REQUIRED)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(BUFEP_ENABLE_DEBUG ON)
endif()

configure_file(${PROJECT_SOURCE_DIR}/include/bufep_config.h.in ${PROJECT_SOURCE_DIR}/include/bufep_config.h)
FILE(GLOB BUFEP_PUBLIC_HEADER "include/*.h")

add_library(bufep SHARED src/bufep.c src/bufep_pmtud.c include/bufep_pmtud.h src/bufep_socket.c include/bufep_socket.h test/test_socket_server.c src/bufep_private.h src/bufep_debug.c include/bufep_debug.h src/bufep_fletcher.c include/bufep_fletcher.h src/bufep_uuidwrapper.c include/bufep_uuidwrapper.h src/bufep_logger.c include/bufep_logger.h)
if (MSVC)
    target_link_libraries(bufep wsock32 ws2_32 rpcrt4)
elseif(LINUX)
    target_link_libraries(bufep ${LibUUID_LIBRARIES})
endif()

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

if(NOT TARGET uninstall)
    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)

    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake)
endif()

if (NOT BUFEP_DISABLE_TESTS)
    enable_testing()
    if (MSVC)
        add_custom_command(TARGET bufep
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:bufep> "${CMAKE_CURRENT_BINARY_DIR}/test/"
                COMMENT "Copy dll file to ${CMAKE_CURRENT_BINARY_DIR} directory" VERBATIM
                )
    endif()
    add_subdirectory(test)
endif()
