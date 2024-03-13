#include <array>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include "question1.h"
#include "question2.h"
#include "question3.h"

int main() {
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

    // Question 2

    /*

    // Creates 5 tools.
    auto t1 = std::make_shared<Tools>();
    auto t2 = std::make_shared<Tools>();
    auto t3 = std::make_shared<Tools>();
    auto t4 = std::make_shared<Tools>();
    auto t5 = std::make_shared<Tools>();

    // Creates 5 robots with the proper tools attached to them
    std::shared_ptr<Robot> r1 = std::make_shared<Robot>(t1, t5);
    std::shared_ptr<Robot> r2 = std::make_shared<Robot>(t1, t2);
    std::shared_ptr<Robot> r3 = std::make_shared<Robot>(t2, t3);
    std::shared_ptr<Robot> r4 = std::make_shared<Robot>(t3, t4);
    std::shared_ptr<Robot> r5 = std::make_shared<Robot>(t4, t5);

    bool isComplete = false; // Condition for the for loop
    auto uncomplete_robots = {r1, r2, r3, r4, r5}; // List to check if all robots have done their task.

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> all_threads;

    while (!isComplete) {
        for (auto& r : uncomplete_robots) {
            // Adds a robot completing its task to the the thread vector, then checks to see if all robots in the robot 
            // vector have completed their task. If this is true, the full loop ends.
            all_threads.emplace_back([&]() {
                    r->completeTask();
                    if (std::all_of(uncomplete_robots.begin(), uncomplete_robots.end(), [](const auto& robot) 
                                                                { return robot->isComplete(); })) {
                        isComplete = true;
                    }
                });
            // Prevents printing two different sets of text on the same line.
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); 
        }
    }

    for (auto& thread : all_threads) {
        thread.join();
    }

    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( stopTime - startTime );

    std::cout << "Total time to complete tasks: " << duration.count() << " seconds" <<std::endl;

    */

    // Question 3

    /*
    Pilot p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;
    auto airTrafficControl = std::make_shared<ATC>();
    std::vector<Pilot> pilotList = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10};

    bool allPilotsLanded = false;
    
    while (allPilotsLanded == false) {
        if (pilotList.empty()) {
            allPilotsLanded = true;
        }
        else {
            for (Pilot& pilots : pilotList) {
                pilots.attemptLand(airTrafficControl);

                if (pilots.flightStatus()) {
                    pilotList.erase(std::find(pilotList.begin(), pilotList.end(), pilots.findPlane()));
                }
            }
        }
    }
    
    */

    return 0;
}
