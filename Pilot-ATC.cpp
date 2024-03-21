#include "Pilot-ATC.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

// General ID of the pilots. Incremented up in constructor to ensure unique ID
int Pilot::genID = 0;
// Static pilot mutex to prevent overlapping outputs
std::mutex Pilot::pilotMtx;

// Sets ATC as awake. 
void AirTrafficController::communicate() {
    std::lock_guard<std::mutex> lock(atcMtx);
    this->asleep = false;
}

// Sets ATC as asleep and ready for communication.
void AirTrafficController::fallAsleep() {
    std::lock_guard<std::mutex> lock(atcMtx);
    this->asleep = true;
}

// Checks if the ATC is asleep
bool AirTrafficController::isAsleep() {
    return asleep;
}

// Pilot lands plane
void Pilot::landPlane() {
    pilotMtx.lock();
    std::cout << "Pilot " << this->myID << " has requested landing." << std::endl;
    std::cout << "Pilot " << this->myID << " has begun landing." << std::endl;
    pilotMtx.unlock();
    
    this->landed = true;
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    this->inPattern = false;

    pilotMtx.lock();
    std::cout << "Pilot " << this->myID << " has landed. Runway is now clear." << std::endl;
    pilotMtx.unlock();
}

// Has pilot enter pattern.
void Pilot::enterPattern() {
    pilotMtx.lock();
    this->inPattern = true;
    std::cout << "Pilot " << this->myID << " has entered traffic pattern." << std::endl;
    pilotMtx.unlock();
}

// Diverts the pilot
void Pilot::divertPilot() {
    pilotMtx.lock();
    std::cout << "Traffic pattern is full. Diverting Pilot " << this->myID << " to another airport." << std::endl;
    this->landed = true;
    pilotMtx.unlock();
}