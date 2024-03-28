#include "headers/Robot-Tools.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

// General robot serial number that creates unique numbers for each new robot.
int Robot::serialNum = 0;

std::mutex toolMutex;

Robot::Robot(std::shared_ptr<Tools> t1, std::shared_ptr<Tools> t2) {
    myTool1 = t1, myTool2 = t2;
    mySerial = serialNum, serialNum++;
}

// Code to pick up tools. Lock the tool mutex to prevent another robot from using it.
void Robot::pickUpTools() {
    toolMutex.lock();
    myTool1->setUse(), myTool2->setUse();
    std::cout << "Robot #" << mySerial << " is picking up tools." << std::endl;
    toolMutex.unlock();

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// Simulation of the robot completing its assigned task.
void Robot::completeTask() {
    // Determines if the tools are in use, if not it will pick them up and execute.
    if (!myTool1->checkIfUsed() && !myTool2->checkIfUsed() && !myTask) {
        pickUpTools();

        toolMutex.lock();
        std::cout << "Robot #" << mySerial << " has begun its task." << std::endl;
        toolMutex.unlock();

        // Completes it task
        myTask = true;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        
        // Returns tools while ensuring no other robot can overlap this task
        toolMutex.lock();
        std::cout << "Robot #" << mySerial << " has completed its task and returned tools." << std::endl;
        myTool1->setUse(), myTool2->setUse();
        toolMutex.unlock();
    }
}

// Checks to see if the tool is in use or not and adjusts its case accordingly
void Tools::setUse() {
    if (!inUse) {
        inUse = true;
    }
    else {
        inUse = false;
    }
}