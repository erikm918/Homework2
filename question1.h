#ifndef QUESTION1
#define QUESTION1

#include <string>
#include <memory>
#include <vector>

// 1.1 

// Creates base sensor class that further classes will be derived from.
class Sensor {
    public:
        virtual void gatherData() = 0;
        virtual void processData() = 0;
};

// 1.2
// Creates 3 sensor classes that are derived from the base Sensor class

// Temperature sensor
class temperatureSensor : public Sensor {
    std::string name = "Temperature";

    public:
        void gatherData() override;
        void processData() override;
};

// Velocity sensor
class velocitySensor : public Sensor {
    std::string name = "Velocity";

    public:
        void gatherData() override;
        void processData() override;
};

// Pressure sensor
class pressureSensor : public Sensor {
    std::string name = "Pressure";

    public:
        void gatherData() override;
        void processData() override;
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