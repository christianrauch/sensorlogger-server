#include <SensorLoggerCommunication.h>
#include <SensorDatabase/SensorDatabase.h>
#include <TempReader/TempReader.h>
#include <TempReader/Sensor.h>

using namespace  ::communication;

class SensorLoggerCommunicationHandler : virtual public SensorLoggerCommunicationIf {
private:
    SensorDatabase *db = NULL;
    TempReader *reader = NULL;

    static ::communication::Sensor fromSensorOW(const ::Sensor &s_ow) {
        ::communication::Sensor s;
        s.family = s_ow.family;
        s.id = s_ow.id;
        s.type = s_ow.type;
        s.time = s_ow.time;
        s.value = s_ow.value;
        s.unit = s_ow.unit;

        return s;
    }

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

    void getSensorValueRange(std::map<int64_t, double> & _return, const std::string& name, const int64_t t_start, const int64_t t_end) {
        // Your implementation goes here
        printf("getSensorRange\n");
    }

    void getSettings(std::vector<std::string> & _return) {
        // Your implementation goes here
        printf("getSettings\n");
        _return = db->getSettings();
    }

    void addSetting(const std::string& name, const std::string& image) {
        // Your implementation goes here
        printf("addSetting\n");
        db->addSetting(name, image.data(), image.size());
    }

    void addSensor(const std::string& name, const std::string& id, const std::string& family, const std::string& type, const std::string& unit, const std::string& setting, const std::vector<double> & position) {
        // Your implementation goes here
        printf("addSensor\n");
        db->addSensor(name, id, family, type, unit, setting, position);
    }

    void getSensorImage(std::string& _return, const std::string& name) {
      // Your implementation goes here
      printf("getSensorImage\n");
      const char* img_data = NULL;
      size_t img_size;
      db->getSettingImage(name, img_data, &img_size);

      if(img_data!=NULL)
        _return = std::string(img_data, img_size);
      else
          std::cerr<<"could not read image from setting "<<name<<std::endl;
    }

    void getSensorOnline(std::vector< ::communication::Sensor > &_return) {
        // Your implementation goes here
        printf("getSensorOnline\n");
        const std::vector< ::Sensor > sensors_ow = reader->getSensors();

        // copy data between different Sensor classes
        for(auto s_ow: sensors_ow) {
            _return.push_back(fromSensorOW(s_ow));
        }
    }

    void getSensorNamesBySetting(std::vector< std::string > & _return, const std::string& name) {
      // Your implementation goes here
      printf("getSensorNamesBySetting\n");
      _return = db->getSensorNames(name);
    }

    void getSensorPosition(std::vector<double> & _return, const std::string& name) {
      // Your implementation goes here
      printf("getSensorPosition\n");
      _return = db->getSensorPosition(name);
    }

    void getSensorByName(communication::Sensor& _return, const std::string& name) {
      // Your implementation goes here
      printf("getSensorByName\n");
      const std::set<std::pair<std::string, std::string>> sensor_addr =
              db->getSensorAddressByName(name);
      std::cout<<"size: "<<sensor_addr.size()<<std::endl;
      // return first element (name is assumed to be unique)
      _return = fromSensorOW(reader->getSensor(sensor_addr.begin()->first,
                                               sensor_addr.begin()->second));
    }
};
