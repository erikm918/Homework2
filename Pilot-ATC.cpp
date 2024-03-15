#include "question3.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

int ATC::traffic = 0;

std::mutex m1;

bool ATC::trafficNumber() {
    if (traffic <= 3) {
        return true;
    }
    else {
        return false;
    }
}

void ATC::addTraffic() {
    traffic++;
}

void ATC::changeSleepStatus() {
    if (isAsleep) {
        isAsleep = false;
    }
    else {
        isAsleep = true;
    }
}

int Pilot::planeNumber = 0;

Pilot::Pilot() {
    myPlane = planeNumber;
    planeNumber++;
}

void Pilot::attemptLand(std::shared_ptr<ATC> air_traffic) {
    // Determines if the plane should be considered for landing.
    if (hasLanded == false) {
        // Determines if there is enough room in the approach pattern. If not it will divert the plane to another airport
        if (air_traffic->trafficNumber()) {
            m1.lock();
            std::cout << "Aircraft #" << myPlane << " requesting landing." << std::endl;
            air_traffic->addTraffic();
            air_traffic->airTrafficOrder.push(myPlane);
            m1.unlock();

            if (air_traffic->airTrafficOrder.front() && air_traffic->sleepStatus()) {
                m1.lock();
                air_traffic->changeSleepStatus();
                std::cout << "Airplane #" << myPlane << " is cleared for landing." << std::endl;
                hasLanded = true;
                std::this_thread::sleep_for(std::chrono::seconds(1));

                std::cout << "Runway is clear." << std::endl;
                air_traffic->changeSleepStatus();
                air_traffic->airTrafficOrder.pop();
                m1.unlock();
            }
        }
        else if (!air_traffic->trafficNumber()) {
            m1.lock();
            std::cout << "Approach pattern full. Aircraft #" << myPlane << " redirected to another airport." << std::endl;
            hasLanded = true;
            m1.unlock();
        } 
    }   
}