#include "question1.h"
#include <iostream>

void temperatureSensor::processData() {
    std::cout << "Processing data from " << this->name << " Sensor." << std::endl;
}

void temperatureSensor::gatherData() {
    std::cout << "Gathering data from " << this->name << " Sensor." << std::endl;
}

void velocitySensor::processData() {
    std::cout << "Processing data from " << this->name << " Sensor." << std::endl;
}

void velocitySensor::gatherData() {
    std::cout << "Gathering data from " << this->name << " Sensor." << std::endl;
}

void pressureSensor::processData() {
    std::cout << "Processing data from " << this->name << " Sensor." << std::endl;
}

void pressureSensor::gatherData() {
    std::cout << "Gathering data from " << this->name << " Sensor." << std::endl;
}

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

void AerospaceControlSystem::addSensor(std::shared_ptr<Sensor> new_sensor) {
    all_sensors.push_back(new_sensor);
}

void AerospaceControlSystem::monitorAndAdjust() {
    for (std::shared_ptr<Sensor> sensor : all_sensors) {
        sensor->gatherData();
        sensor->processData();
        std::cout << "Adjusting controls based on sensor data." << std::endl;
    }
}