#include "question2.h"
#include <iostream>
#include <thread>
#include <chrono>

int Robot::serialNum = 0;

Robot::Robot(std::shared_ptr<Tools> t1, std::shared_ptr<Tools> t2) {
    myTool1 = t1, myTool2 = t2;
    mySerial = serialNum, serialNum++;
}

void Robot::completeTask() {
    if (!myTool1->checkIfUsed() && !myTool2->checkIfUsed() && !myTask) {
        myTool1->setUse(), myTool2->setUse();
        std::cout << "Robot #" << mySerial << " is picking up tools." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "Robot #" << mySerial << " has begun its task." << std::endl;

        myTask = true;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        
        std::cout << "Robot #" << mySerial << " has completed its task and returned tools." << std::endl;
        myTool1->setUse(), myTool2->setUse();
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