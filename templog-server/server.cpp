#include <SensorDatabase/SensorDatabase.h>
#include <TempReader/TempReader.h>
#include <pthread.h>
#include <iostream>
#include "Timer.h"
#include "logger.h"

#include <CommunicationService/SensorLoggerCommunicationServer.h>

void dbg_db_fake(SensorDatabase &db) {
    db.reset();
    db.addSetting("basement");
    db.addSensor("pipe", "67C6697351FF", "28", "DS18B20", "°C", "basement");
    db.addSensor("oven", "4AEC29CDBAAB", "10", "DS18B20", "°C", "basement");
    db.addSensor("watertank", "F2FBE3467CC2", "10", "DS18B20", "°C", "basement");
}

void dbg_reader_fake(TempReader &reader) {
    reader.addFake("10");
    reader.addFake("10");
    reader.addFake("28");
}

int main() {
    SensorDatabase db;
    TempReader reader;

    db.open("logger.db");

    std::cout<<"addr db: "<<&db<<std::endl;
    std::cout<<"addr reader: "<<&reader<<std::endl;
    // init with example data
    dbg_db_fake(db);
    dbg_reader_fake(reader);

    reader.open();

    const time_t period = 2; // seconds

    LoggerConfig conf = {.period=period, .db=&db,
        .reader=&reader, .setting="keller"};

    pthread_t th_logger;

    std::cout<<"addr per: "<<&period<<std::endl;
    std::cout<<"addr conf: "<<&conf<<std::endl;

    //pthread_create(&th_logger, NULL, logger, (void*)period);
    pthread_create(&th_logger, NULL, logger, &conf);
    //pthread_create(&th_logger, NULL, logger, NULL);

    SensorLoggerCommunicationServer s(9090, db, reader);

    s.start();

    pthread_join(th_logger, NULL);

    std::cout<<"exit..."<<std::endl;
}
