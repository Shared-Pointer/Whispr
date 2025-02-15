cmake_minimum_required(VERSION 3.15...3.31)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED 20)

project(Whispr
    VERSION 1.0
    DESCRIPTION "Whispr communicator"
    LANGUAGES CXX
    )

set(SOURCES
  src/whispr_server.cpp
  src/server_socket.cpp
)

set(HEADERS
  include/server_socket.h
)

add_executable(whispr ${SOURCES} ${HEADERS})
