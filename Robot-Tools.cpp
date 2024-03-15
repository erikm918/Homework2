#include "Robot-Tools.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

int Robot::serialNum = 0;

std::mutex toolMutex;

Robot::Robot(std::shared_ptr<Tools> t1, std::shared_ptr<Tools> t2) {
    myTool1 = t1, myTool2 = t2;
    mySerial = serialNum, serialNum++;
}

void Robot::pickUpTools() {
    toolMutex.lock();
    myTool1->setUse(), myTool2->setUse();
    std::cout << "Robot #" << mySerial << " is picking up tools." << std::endl;
    toolMutex.unlock();

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Robot::completeTask() {
    if (!myTool1->checkIfUsed() && !myTool2->checkIfUsed() && !myTask) {
        pickUpTools();

        toolMutex.lock();
        std::cout << "Robot #" << mySerial << " has begun its task." << std::endl;
        toolMutex.unlock();

        myTask = true;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        
        toolMutex.lock();
        std::cout << "Robot #" << mySerial << " has completed its task and returned tools." << std::endl;
        myTool1->setUse(), myTool2->setUse();
        toolMutex.unlock();
    }
}

void Tools::setUse() {
    if (!inUse) {
        inUse = true;
    }
    else {
        inUse = false;
    }
}