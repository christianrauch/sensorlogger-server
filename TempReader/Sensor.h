#include <string>

struct Sensor {
    std::string id;
    std::string family;
    std::string type;
    double value;

    Sensor(const std::string family, const std::string id, const std::string type, const double value):family(family),id(id),type(type),value(value) {};
};
