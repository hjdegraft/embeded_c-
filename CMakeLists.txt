cmake_minimum_required(VERSION 3.3.1)
project(embed-ledcontrol)

set(LEDCONTROL_VERSION 1.0.0)

include (FindPackageHandleStandardArgs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(densityd REQUIRED)
#find_library(LIBSQLITE NAMES sqlite3)
#find_package(RapidJSON REQUIRED)
#find_package(CURL REQUIRED) 

#find_package(UUID REQUIRED)
#include_directories(${LIBUUID_INCLUDE_DIR})

#find_package(Libuv REQUIRED)
#include_directories(${LIBUV_INCLUDE_DIR})

#find_package(ZeroMQ REQUIRED)
#include_directories(${ZeroMQ_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DCONFIGD_NO_HTTP_DEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall")

enable_testing()
