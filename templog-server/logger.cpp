#include "Timer.h"
#include "logger.h"

void *logger(void* config) {
    // read configuration
    SensorDatabase *db = (*(LoggerConfig*) config).db;
    TempReader *reader = (*(LoggerConfig*) config).reader;
    const time_t period = (*(LoggerConfig*) config).period;
    
    // set timer for periodic thread
    Timer timer;
    timer.set(period);

    /*
        Changes in the database are expected in operation and should be
        considered when reading values. Fetching target sensor addresses
        is therefore required in every cycle.
    */

    // fetch data periodically until process is killed
    while(true) {
        // iterate all settings
        const std::vector<std::string> setting_names = db->getSettings();
        for(auto setting: setting_names) {
            // iterate sensor names of setting
            const std::vector<std::string> sensor_names = db->getSensorNames(setting);
            for(auto sname: sensor_names) {
                const std::set<std::pair<std::string, std::string>> sensor_addresses =
                    db->getSensorAddressByName(sname);

                if(sensor_addresses.size()!=1) {
                    std::cerr<<"Single sensor ID expected for "<<sname<<" (got "<<sensor_addresses.size()<<")"<<std::endl;
                }

                // iterate sensor addresses of sensor name
                for(auto saddr: sensor_addresses) {
                    try {
                        const Sensor s = reader->getSensor(saddr.first, saddr.second);
                        db->addValue(sname, s.time, s.value);
                    }
                    catch (std::invalid_argument &e) {
                        // reading value from sensor failed
                        // do nothing (value won't be added to database)
                        std::cerr<<"Could not read from sensor "<<saddr.first<<"."<<saddr.second<<" !"<<std::endl;
                    }
                } // sensor_addresses
            } // sensor_names
        } // setting_names

        // wait until end of period
        timer.wait();
    }
}

