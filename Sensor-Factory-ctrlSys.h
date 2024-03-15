#ifndef QUESTION1
#define QUESTION1

#include <string>
#include <memory>
#include <vector>

// 1.1 

// Creates base sensor class that further classes will be derived from.
class Sensor {
    protected:
    std::string name;

    public:
        virtual void gatherData();
        virtual void processData();
};

// 1.2
// Creates 3 sensor classes that are derived from the base Sensor class

// Temperature sensor
class temperatureSensor : public Sensor {
    public:
        temperatureSensor() {this->name = "Temperature";}
};

// Velocity sensor
class velocitySensor : public Sensor {
    public:
        velocitySensor() {this->name = "Velocity";}
};

// Pressure sensor
class pressureSensor : public Sensor {
    public:
        pressureSensor() {this->name = "Pressure";}
};

// 1.3

// Class that allows for the creation of sensors based on desired type. Returns null pointer if no type exists.
class SensorFactory {
    public:
        static std::shared_ptr<Sensor> createSensor(std::string sensor_type);
};

// 1.4

// Creates a control system that adds sensors using the sensor factory and contains a monitor and adjust function
class AerospaceControlSystem {
    std::vector<std::shared_ptr<Sensor>> all_sensors;

    public:
        void addSensor(std::shared_ptr<Sensor> new_sensor);
        void monitorAndAdjust();
};

#endif