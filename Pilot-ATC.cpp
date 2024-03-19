#include "Pilot-ATC.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

// General ID of the pilots. Incremented up in constructor to ensure unique ID
int Pilot::genID = 0;

// Sets ATC as asleep or awake.
void AirTrafficControler::communicate() {
    atcMtx.lock();
    this->asleep = false;
    atcMtx.unlock();
}

void AirTrafficControler::fallAsleep() {
    atcMtx.lock();
    this->asleep = true;
    atcMtx.unlock();
}

// Checks if the ATC is asleep
bool AirTrafficControler::isAsleep() {
    atcMtx.lock();
    bool sleepStatus = asleep;
    atcMtx.unlock();
    return sleepStatus;
}

// Sets the bool value of whether the plane is in the pattern when it enters and leaves (lands/diverts).
void Pilot::enterPattern() {
    this->inPattern = true;
    std::cout << "Pilot " << this->myID << " is in the traffic pattern." << std::endl;
}

void Pilot::leavePattern() {
    this->inPattern = false;
}


void Pilot::landPlane() {
    pilotMtx.lock();
    std::cout << "Pilot " << this->myID << " has begun landing." << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(1)); 

    this->setLanding();

    std::cout << "Pilot " << this->myID << " has landed. Runway is now clear." << std::endl;
    pilotMtx.unlock();
}