#include <string>
#include <ctime>

struct Sensor {
    time_t time;
    std::string id;
    std::string family;
    std::string type;
    double value;

    Sensor(const std::string family, const std::string id, const std::string type, const time_t time, const double value):family(family),id(id),type(type),time(time),value(value) {};
};
