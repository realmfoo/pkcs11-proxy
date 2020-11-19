cmake_minimum_required(VERSION 3.13)

if (COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif (COMMAND cmake_policy)

project(pkcs11 C)

set(CMAKE_C_STANDARD 99)
set(PKCS11_PROXY_SRCS gck-rpc-module.c gck-rpc-message.c gck-rpc-util.c egg-buffer.c)
if (NOT WIN32)
    set(PKCS11_DAEMON_SRCS egg-buffer.c gck-rpc-daemon-standalone.c gck-rpc-dispatch.c gck-rpc-message.c gck-rpc-util.c)
endif ()

add_definitions(-Wall)
add_library(pkcs11-proxy SHARED ${PKCS11_PROXY_SRCS})

# Disable console when building Win32 binary in release mode
if (WIN32)
    add_definitions(-DUNICODE)
    option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
    if ("${CMAKE_BUILD_TYPE}" MATCHES "^Rel.*")
        set(GUI_TYPE WIN32)
    endif ()
endif ()

if (NOT WIN32)
    add_executable(pkcs11-daemon ${GUI_TYPE} ${PKCS11_DAEMON_SRCS})
endif ()

set_target_properties(pkcs11-proxy PROPERTIES VERSION 0.1 SOVERSION 0)

if (WIN32)
    target_link_libraries(pkcs11-proxy ws2_32)
else ()
    target_link_libraries(pkcs11-proxy pthread)
    target_link_libraries(pkcs11-daemon dl pthread)
    install(TARGETS pkcs11-proxy
            DESTINATION /usr/lib
            COMPONENT proxy)
    install(TARGETS pkcs11-daemon
            DESTINATION /usr/bin
            COMPONENT daemon)

    set(CPACK_SYSTEM_NAME "amd64")
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Konstantin Leboev <konstantin.leboev@gmail.com")
    set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/debian/changelog")
    set(CPACK_DEB_COMPONENT_INSTALL ON)
#    set(CPACK_DEBIAN_PROXY_PACKAGE_NAME "pkcs11-proxy")
#    set(CPACK_DEBIAN_DAEMON_PACKAGE_NAME "pkcs11-daemon")
    include(CPack)
endif ()
