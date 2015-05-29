#include <iostream>
#include <SensorDatabase.h>
#include <TempReader.h>

struct LoggerConfig {
    time_t period;          // period in seconds
    SensorDatabase *db;     // pointer to database
    TempReader *reader;     // pointer to reader
    std::string setting;    // setting to fetch sensors from
};

void *logger(void* config);
