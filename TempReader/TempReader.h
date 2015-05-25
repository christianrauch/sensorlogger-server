#include <owcapi.h>
#include "Sensor.h"
#include <vector>

class TempReader {
    private:
        std::string ow_arguments;

        std::string getValueFromPath(const std::string path);

    public:
        TempReader();
        ~TempReader();

        // open, close
        void open();
        void close();

        // arguments
        void setDevice(const std::string path);

        void addArguments(const std::string args);

        void addFake(const std::string family);

        // reading single sensor value
        Sensor getSensor(const std::string family, const std::string id);
        // get all sensors
        std::vector<Sensor> getSensors();
};
