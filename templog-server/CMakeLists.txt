add_executable(server server.cpp)
target_link_libraries(server sensor_database temp_reader)
