#include "Sensor-Factory-ctrlSys.h"
#include <iostream>

// Simulation of processing/gathering data. Allows for inheritance of funciton.
void Sensor::gatherData() {
    std::cout << "Gathering data from " << this->name << " Sensor." << std::endl;
}

void Sensor::processData() {
    std::cout << "Processing data from " << this->name << " Sensor." << std::endl;
}

/*
    Determines which type of sensor should be created and creates it as a shared pointer that can be used in the 
    control system. If a supported type is not chosen a null pointer is returned to prevent oddities. 
*/
std::shared_ptr<Sensor> SensorFactory::createSensor(std::string sensor_type) {
    if (sensor_type == "Temperature") {
        return std::make_shared<temperatureSensor>();
    }
    else if (sensor_type == "Velocity") {
        return std::make_shared<velocitySensor>();
    }
    else if (sensor_type == "Pressure") {
        return std::make_shared<pressureSensor>();
    }
    else {
        return nullptr;
    }
}

// Adds sensors to its system.
void AerospaceControlSystem::addSensor(std::shared_ptr<Sensor> new_sensor) {
    all_sensors.push_back(new_sensor);
}

// Gathers and processes data and simulates control adjustment.
void AerospaceControlSystem::monitorAndAdjust() {
    for (std::shared_ptr<Sensor> sensor : all_sensors) {
        sensor->gatherData();
        sensor->processData();
        std::cout << "Adjusting controls based on sensor data." << std::endl;
    }
}