message("modules" ${CMAKE_MODULE_PATH})

find_package(OWFS REQUIRED)

include_directories(${OWFS_INCLUDE_DIRS})

add_library(temp_reader TempReader.cpp)
target_link_libraries(temp_reader ${OWFS_LIBRARIES})
