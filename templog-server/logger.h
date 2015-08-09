#include <iostream>
#include <SensorDatabase/SensorDatabase.h>
#include <TempReader/TempReader.h>

struct LoggerConfig {
    time_t period;          // period in seconds
    SensorDatabase *db;     // pointer to database
    TempReader *reader;     // pointer to reader
};

void *logger(void* config);
