#include <sqlite3.h>
#include <vector>
#include <map>

class SensorDatabase {
    private:
        sqlite3 *db;

    public:
        SensorDatabase() {};
        SensorDatabase(const std::string path);
        ~SensorDatabase();

        void init();
        void remove();
        void close();
        int open(const std::string path);
        sqlite3* getdb() {return db;};

        void addSetting(const std::string name);

        void addSensor(const std::string name, const std::string id, const std::string type,
                       const std::string unit, const std::string setting,
                       const unsigned int pos_x, const unsigned int pos_y);

        void addValue(const std::string sensor_name,
                      const long long time, const double value);

        std::map<long long, double> getValueRange(const std::string sensor_name,
                                          const long long start, const long long end);

        std::vector<std::string> getSensorsString(const std::string setting, const std::string value_type);

        std::vector<std::string> getSensorsName(const std::string setting) {
            return getSensorsString(setting, "name");
        }

        std::vector<std::string> getSensorsID(const std::string setting) {
            return getSensorsString(setting, "id");
        };

};

