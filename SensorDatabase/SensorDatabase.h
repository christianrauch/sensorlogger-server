#ifndef __SENSORDATABASE_H__
#define __SENSORDATABASE_H__

#include <sqlite3.h>
#include <vector>
#include <map>
#include <set>

class SensorDatabase {
    private:
        sqlite3 *db;

    public:
        SensorDatabase() {};
        SensorDatabase(const std::string path);
        ~SensorDatabase();

        void init();

        void remove();

        void reset() {
            remove();
            init();
        }

        void close();

        int open(const std::string path);

        sqlite3* getdb() {return db;};

        void addSetting(const std::string name, const char* img_data = NULL, const size_t img_size = 0);

        void addSensor(const std::string name, const std::string id, const std::string family, const std::string type,
                       const std::string unit, const std::string setting,
                       const std::vector<double> position = {0.0, 0.0});

        void addValue(const std::string sensor_name,
                      const long long time, const double value);

        std::vector<std::string> getSettings();

        std::map<long long, double> getValueRange(const std::string sensor_name,
                                          const long long start, const long long end);

        std::vector<std::string> getSensorsString(const std::string setting, const std::string value_type);

        std::vector<std::string> getSensorNames(const std::string setting) {
            return getSensorsString(setting, "name");
        }

        std::vector<std::string> getSensorIDs(const std::string setting) {
            return getSensorsString(setting, "id");
        };

        std::set<std::pair<std::string, std::string>> getSensorAddress(const std::string key, const std::string value);

        std::set<std::pair<std::string, std::string>> getSensorAddressBySetting(const std::string setting) {
            return getSensorAddress("setting", setting);
        }

        // return sensor address as pair (family,id)
        std::set<std::pair<std::string, std::string>> getSensorAddressByName(const std::string name) {
            // there should be only one address per sensor name, as names are
            // unique, but we will return a whole set anyway
            return getSensorAddress("name", name);
        }

        std::vector<double> getSensorPosition(const std::string name);

        void getSettingImage(const std::string name, const char* img_data, size_t* img_size);
};

#endif
