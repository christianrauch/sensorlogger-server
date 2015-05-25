#include "TempReader.h"
#include <iostream>
#include <cstring>

TempReader::TempReader() {
    ow_arguments = "";
}

TempReader::~TempReader() {
    close();
}

void TempReader::open() {
    OW_init(ow_arguments.c_str());
}

void TempReader::close() {
    OW_finish();
}

void TempReader::setDevice(const std::string path) {
    ow_arguments += " --passive="+path;
}

void TempReader::addArguments(const std::string args) {
    ow_arguments += args;
}

void TempReader::addFake(const std::string family) {
    ow_arguments += " --fake "+family;
}

Sensor TempReader::getSensor(const std::string family, const std::string id) {

    const std::string path_sensor = family+'.'+id;

    const std::string path_type = "/"+path_sensor+"/type";
    const std::string path_temp = "/"+path_sensor+"/temperature";

    const std::string type = getValueFromPath(path_type);
    const double temp = std::stod(getValueFromPath(path_temp));

    return Sensor(family, id, type, temp);
}

std::vector<Sensor> TempReader::getSensors() {
    std::vector<Sensor> sensors;

    char *buffer = NULL;
    // get root ("/")
    OW_get(NULL, &buffer, NULL);

    std::cout<<"content: "<<buffer<<std::endl;

    char *entry;
    while((entry = strsep(&buffer, ",")) != NULL) {
        std::cout<<entry;

        const std::string path_id = "/"+std::string(entry)+"id";
        const std::string path_family = "/"+std::string(entry)+"family";

        const std::string family = getValueFromPath(path_family);
        const std::string id = getValueFromPath(path_id);

        if(!family.empty() && !id.empty()) {
            std::cout<<"\t<-- sensor";
            sensors.push_back(getSensor(family, id));
        }

        std::cout<<std::endl;
    }

    free(entry);
    entry = NULL;
    free(buffer);
    buffer = NULL;

    return sensors;
};

std::string TempReader::getValueFromPath(const std::string path) {
    char *buffer = NULL;
    std::string value;
    const int ret = OW_get(path.c_str(), &buffer, NULL);

    if(ret>=0)
        value = std::string(buffer);

    free(buffer);
    buffer = NULL;

    return value;
}
