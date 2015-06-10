#include "SensorLoggerCommunication.h"

using namespace  ::communication;

class SensorLoggerCommunicationHandler : virtual public SensorLoggerCommunicationIf {
private:
    SensorDatabase *db;
    TempReader *reader;

public:
    SensorLoggerCommunicationHandler(SensorDatabase &db, TempReader &reader){
        std::cout<<"db Handle: "<<&db<<std::endl;
        this->db = &db;
        this->reader = &reader;
        std::cout<<"db Handle (this): "<<this->db<<std::endl;
        std::cout<<"reader Handle (this): "<<this->reader<<std::endl;
    }

    double getSensorValue(const std::string& name) {
        // Your implementation goes here
        printf("getSensorValue\n");
        std::cout<<"db: "<<db<<std::endl;
    }

    void getSensorRange(std::map<int64_t, double> & _return, const std::string& name, const int64_t t_start, const int64_t t_end) {
        // Your implementation goes here
        printf("getSensorRange\n");
    }

    void addSetting(const std::string& name, const std::string& image) {
        // Your implementation goes here
        printf("addSetting\n");
    }

    void addSensor(const std::string& name, const std::string& id, const std::string& family, const std::string& type, const std::string& unit, const std::string& setting) {
        // Your implementation goes here
        printf("addSensor\n");
    }

    void getSensorOnline(std::vector< ::communication::Sensor > & _return) {
      // Your implementation goes here
      printf("getSensorOnline\n");
    }

};

