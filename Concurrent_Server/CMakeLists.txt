cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++11 -pthread")
project(Concurrent_server)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

set(SRC
    ${PROJECT_SOURCE_DIR}/src/ThreadPool.cpp
    ${PROJECT_SOURCE_DIR}/src/TaskQueue.cpp
    ${PROJECT_SOURCE_DIR}/src/Server.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

set(LIB_NAME Concurrent_server_lib)

add_library(${LIB_NAME} STATIC ${SRC})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} ${SRC})

