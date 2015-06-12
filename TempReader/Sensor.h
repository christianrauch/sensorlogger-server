#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <string>
#include <ctime>

struct Sensor {
    time_t time;
    std::string id;
    std::string family;
    std::string type;
    double value;
    std::string unit;

    Sensor(const std::string family, const std::string id, const std::string type,
           const time_t time, const double value, const std::string unit):
        family(family),id(id),type(type),time(time),value(value),unit(unit) {}
};

#endif
