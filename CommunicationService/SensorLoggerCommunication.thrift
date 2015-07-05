namespace cpp communication
namespace py communication

struct Sensor {
    1: i64 time;
    2: string id
    3: string family
    4: string type
    5: double value
    6: string unit
}

service SensorLoggerCommunication {

    // return list of all available settings
    list<string> getSettings()

    // add new setting with name and image to database
    oneway void addSetting(1: string name, 2: binary image)

    // get all sensors that are currently connected
    // we use list instead of set, as set needs the comparing operation (<) for type Sensor
    list<Sensor> getSensorOnline()

    // add sensor by family and id to setting
    oneway void addSensor(1: string name, 2: string id, 3: string family, 4: string type,
        5: string unit, 6: string setting, 7: list<double> position)

    // get sensors and values of setting
    list<string> getSensorNamesBySetting(1: string name)

    // get sensor value
    double getSensorValue(1: string name)

    // get sensor value in time range
    map<i64,double> getSensorValueRange(1: string name, 2: i64 t_start, 3: i64 t_end)

    list<double> getSensorPosition(1: string name)
}
