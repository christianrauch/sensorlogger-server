# Timer for periodic threads
add_library(timer Timer.cpp)

# logger to periodically log data
add_library(logger logger.cpp)
target_link_libraries(logger timer)

# main executable
add_executable(server server.cpp)
target_link_libraries(server sensor_database temp_reader logger)
target_link_libraries(server pthread)

