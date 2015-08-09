cmake_minimum_required(VERSION 2.6)

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
add_definitions(-DDEBUG)
endif()

project(TempLogger)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_subdirectory(SensorDatabase)
add_subdirectory(TempReader)
add_subdirectory(CommunicationInterface)
add_subdirectory(CommunicationService)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(templog-server)

