#include "question1.h"

void Question1() {
    // 1.5
    AerospaceControlSystem ctrlSys;
    SensorFactory factory;

    /* Creates an array that store the three different sensor types, then using a for loop creates and adds the
       designated sensor type to the ctrlSys. */
    std::string sensor_types[3] = {"Temperature", "Velocity", "Pressure"};
    for (std::string types : sensor_types) {
        ctrlSys.addSensor(factory.createSensor(types));
    }

    ctrlSys.monitorAndAdjust();
}