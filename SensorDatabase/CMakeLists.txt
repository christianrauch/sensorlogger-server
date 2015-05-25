message("modules" ${CMAKE_MODULE_PATH})

find_package(SQLite3 REQUIRED)

include_directories(${SQLITE3_INCLUDE_DIRS})

add_library(sensor_database SensorDatabase.cpp)
target_link_libraries(sensor_database ${SQLITE3_LIBRARIES})
