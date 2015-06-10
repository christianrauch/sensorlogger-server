# input and output of thrift compiler
set(T_FILE "SensorLoggerCommunication.thrift")
set(T_SOURCE "thrift-service-cpp")

set(T_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${T_FILE})
set(T_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${T_SOURCE})

# find executable
find_program(THRIFT_BIN thrift)

# generate code
if (THRIFT_BIN)
    message("Found thrift compiler at: " ${THRIFT_BIN})
    # only generate code if folder does not already exist
#    if (NOT EXISTS ${T_SOURCE_PATH})
    	file(MAKE_DIRECTORY ${T_SOURCE_PATH})
    	execute_process(COMMAND ${THRIFT_BIN} -r --gen cpp -out ${T_SOURCE_PATH} ${T_FILE_PATH})
#    endif(NOT EXISTS ${T_SOURCE_PATH})
else(THRIFT_BIN)
    message(SEND_ERROR "Cannot find thrift compiler in path.")
endif(THRIFT_BIN)

# source files for service
file(GLOB SERVICE_SRC ${T_SOURCE_PATH}/*.cpp)
# skeleton files to remove
file(GLOB SERVICE_SKEL_SRC ${T_SOURCE_PATH}/*_server.skeleton.cpp)
list(REMOVE_ITEM SERVICE_SRC ${SERVICE_SKEL_SRC})
#message("sources" ${SERVICE_SRC})

add_library(sensor_logger_communication_base ${SERVICE_SRC})

include_directories(${T_SOURCE_PATH})
include_directories(${CMAKE_SOURCE_DIR}/SensorDatabase)
include_directories(${CMAKE_SOURCE_DIR}/TempReader)

add_library(sensor_logger_communication SensorLoggerCommunicationServer.cpp)
target_link_libraries(sensor_logger_communication sensor_logger_communication_base)
target_link_libraries(sensor_logger_communication -lthrift)

