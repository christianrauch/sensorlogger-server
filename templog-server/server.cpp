#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <cstdlib>
#include <unistd.h>

#include "SensorDatabase.h"
#include "TempReader.h"

void db_test() {
    SensorDatabase db;
    int ret = db.open("logger.db");
    std::cout<<"ret: "<<ret<<std::endl;
    if (db.open("logger.db") != SQLITE_OK) {
        std::cout<<"error"<<std::endl;
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db.getdb()));
    }

    //db.remove();
    db.init();
    db.addSetting("keller");
    db.addSensor("rohr", "DS18B20BB", "DS18B20", "°C", "keller", 34, 145);
    db.addSensor("ofen", "DS18B20BB", "DS18B20", "°C", "keller", 34, 145);
    db.addValue("ofen", 1431777348, 37.7);
    for (unsigned int t=1431777338; t<=1431777338+100; t++) {
        db.addValue("ofen", t, 37.7+(t-1431777338)*0.1);
    }
    std::cout<<"reading..."<<std::endl;
    std::map<long long, double> values = db.getValueRange("ofen", 1431777340, 1431777400);
    for (auto& x: values) {
        std::cout << x.first << ": " << x.second << '\n';
    }

    std::vector<std::string> names = db.getSensorsName("keller");
    for (int i=0; i<names.size(); i++) {
        std::cout << names[i] << std::endl;
    }

    std::cout<<"done"<<std::endl;
    db.close();

}


void reader_test() {
    TempReader reader;

    //reader.addArguments("--fake 10 --fake 28");
    reader.addFake("10");
    reader.addFake("28");
    reader.open();
    std::vector<Sensor> sensors = reader.getSensors();

    for(auto s: sensors) {
        std::cout<<s.id<<": "<<s.value<<std::endl;
    }

    reader.close();
}


int main() {
    SensorDatabase db;
    TempReader reader;

    db.open("logger.db");

    reader.addFake("10");
    reader.addFake("10");
    reader.addFake("28");
    reader.open();

    db.init();

    db.addSetting("basement1");
    
    std::cout<<"adding sensors.."<<std::endl;
    const std::vector<Sensor> sensors_name = reader.getSensors();
    for(auto s: sensors_name) {
        std::cout<<"adding "<<s.id<<" ("<<s.type<<")"<<std::endl;
        db.addSensor(s.id, s.id, s.type, "°C", "basement1", 0, 0);
    }

    std::cout<<"reading values..."<<std::endl;
    for(unsigned int i=0; i<=10; i++) {
        const std::vector<Sensor> sensors = reader.getSensors();
        for(auto s: sensors) {
            std::cout<<"adding "<<s.id<<" with "<<s.value<<std::endl;
            db.addValue(s.id, s.time, s.value);
        }
        sleep(10);
    }

}
