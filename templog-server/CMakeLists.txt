find_package(GLIB REQUIRED)

include_directories(${GLIB_INCLUDE_DIRS})

# Timer for periodic threads
add_library(timer Timer.cpp)

# logger to periodically log data
add_library(logger logger.cpp)
target_link_libraries(logger timer)

# main executable
add_executable(sensorlogger-server server.cpp)
target_link_libraries(sensorlogger-server sensor_database temp_reader logger)
target_link_libraries(sensorlogger-server sensor_logger_communication_server)
target_link_libraries(sensorlogger-server pthread)
target_link_libraries(sensorlogger-server ${GLIB_LIBRARIES})

install(TARGETS sensorlogger-server
        RUNTIME DESTINATION bin)

