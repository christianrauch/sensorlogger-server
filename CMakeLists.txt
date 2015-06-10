cmake_minimum_required(VERSION 2.6)

project(TempLogger)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_subdirectory(SensorDatabase)
add_subdirectory(TempReader)
add_subdirectory(CommunicationService)

include_directories(SensorDatabase TempReader CommunicationService)

add_subdirectory(templog-server)

