#include <iostream>
#include "SensorDatabase.h"

SensorDatabase::SensorDatabase(const std::string path) {
    open(path);
}

SensorDatabase::~SensorDatabase() {
    close();
}

void SensorDatabase::init() {
    // create tables
    char *err = 0;

    const std::string sql_create_settings =
        "CREATE TABLE settings (name TEXT PRIMARY KEY UNIQUE);";
    const std::string sql_create_sensors =
        "CREATE TABLE sensors (name TEXT PRIMARY KEY UNIQUE, id TEXT, type TEXT, unit TEXT, setting TEXT, posx INT, posy INT);";
    const std::string sql_create_data =
        "CREATE TABLE data (sensor TEXT, time INT, value REAL, PRIMARY KEY(sensor, time));";
    
    sqlite3_exec(db, sql_create_settings.c_str(), 0, 0, &err);
    if(err!=NULL)
        std::cout<<"error: "<<err<<std::endl;
    sqlite3_exec(db, sql_create_sensors.c_str(), 0, 0, &err);
    if(err!=NULL)
        std::cout<<"error: "<<err<<std::endl;
    sqlite3_exec(db, sql_create_data.c_str(), 0, 0, &err);
    if(err!=NULL)
        std::cout<<"error: "<<err<<std::endl;
}

void SensorDatabase::remove() {
    const std::string sql_delete_table =
        "DROP TABLE IF EXISTS settings;"
        "DROP TABLE IF EXISTS sensors;"
        "DROP TABLE IF EXISTS data;";
    sqlite3_exec(db, sql_delete_table.c_str(), 0, 0, 0);
}

void SensorDatabase::close() {
    sqlite3_close(db);
}

int SensorDatabase::open(const std::string path) {
    return sqlite3_open(path.c_str(), &db);
}

void SensorDatabase::addSetting(const std::string name) {
    char *err = 0;
    const std::string sql_add_setting =
        "INSERT INTO settings VALUES ('"+name+"');";

    sqlite3_exec(db, sql_add_setting.c_str(), 0, 0, &err);
    if(err!=NULL) {
        std::cout<<"error: "<<err<<std::endl;
        sqlite3_free(err);
    }
}

void SensorDatabase::addSensor(const std::string name, const std::string id, const std::string type,
                               const std::string unit, const std::string setting,
                               const unsigned int pos_x, const unsigned int pos_y)
{
    char *err = 0;
    const std::string sql_add_sensor =
    "INSERT INTO sensors VALUES ('"+name+"', '"+id+"', '"+type+"', '"+unit+"', '"+setting+"','"+std::to_string(pos_x)+"', '"+std::to_string(pos_y)+"');";

    sqlite3_exec(db, sql_add_sensor.c_str(), 0, 0, &err);
    if(err!=NULL) {
        std::cout<<"error: "<<err<<std::endl;
        sqlite3_free(err);
    }
}

void SensorDatabase::addValue(const std::string sensor_name, const long long time, const double value) {
    char *err = 0;
    const std::string sql_add_value =
        "INSERT INTO data VALUES ('"+sensor_name+"', "+std::to_string(time)+", "+std::to_string(value)+");";

    sqlite3_exec(db, sql_add_value.c_str(), 0, 0, &err);
    if(err!=NULL) {
        std::cout<<"error: "<<err<<std::endl;
        sqlite3_free(err);
    }
}

std::map<long long, double> SensorDatabase::getValueRange(const std::string sensor_name,
                                                  const long long start, const long long end)
{
    std::map<long long, double> values;
    const std::string sql_get_valuerange =
        "SELECT time, value FROM data WHERE sensor='"+sensor_name+"' AND time BETWEEN "+std::to_string(start)+" AND "+std::to_string(end)+";";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql_get_valuerange.c_str(), -1, &stmt, 0);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        const long long time = sqlite3_column_int64(stmt, 0);
        const double val = sqlite3_column_double(stmt, 1);
        values[time] = val;
    }
    sqlite3_finalize(stmt);

    return values;
}

std::vector<std::string> SensorDatabase::getSensorsString(const std::string setting, const std::string value_type) {
    std::vector<std::string> sensors_value;

    const std::string sql_get_sensors_value =
        "SELECT "+value_type+" FROM sensors WHERE setting='"+setting+"';";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql_get_sensors_value.c_str(), -1, &stmt, 0);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        const std::string val = (char*)sqlite3_column_text(stmt, 0);
        sensors_value.push_back(val);
    }
    sqlite3_finalize(stmt);

    return sensors_value;
}

