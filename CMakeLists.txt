cmake_minimum_required (VERSION 2.4)

if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project (pkcs11 C)

set(CMAKE_C_STANDARD 99)
set(PKCS11_PROXY_SRCS gck-rpc-module.c gck-rpc-message.c gck-rpc-util.c egg-buffer.c)
if (NOT WIN32)
    set(PKCS11_DAEMON_SRCS egg-buffer.c gck-rpc-daemon-standalone.c gck-rpc-dispatch.c gck-rpc-message.c gck-rpc-util.c)
endif()

add_definitions(-Wall)
add_library(pkcs11-proxy SHARED ${PKCS11_PROXY_SRCS})

# Disable console when building Win32 binary in release mode
if (WIN32)
  add_definitions(-DUNICODE)
  option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
  if("${CMAKE_BUILD_TYPE}" MATCHES "^Rel.*")
    set(GUI_TYPE WIN32)
  endif()
endif()

if (NOT WIN32)
    add_executable (pkcs11-daemon ${GUI_TYPE} ${PKCS11_DAEMON_SRCS})
endif()

set_target_properties(pkcs11-proxy PROPERTIES VERSION 0.1 SOVERSION 0)

if (WIN32)
  target_link_libraries (pkcs11-proxy ws2_32)
else()
    target_link_libraries (pkcs11-proxy pthread)
    target_link_libraries (pkcs11-daemon dl pthread)
    install_targets (/lib pkcs11-proxy)
    install_targets (/bin pkcs11-daemon)
endif()
