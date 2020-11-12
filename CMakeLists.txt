cmake_minimum_required(VERSION 3.12.2)
project(unix_socket CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(server server.cpp)
add_executable(client client.cpp)

set(CPACK_GENERATOR "DEB")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Unix socket client-server")
set(CPACK_PACKAGE_VENDOR "Kokorev")
set(CPACK_PACKAGE_CONTACT "Kokorev Y.S. <kokorev.yaroslav@gmail.com>")

include(CPack)
