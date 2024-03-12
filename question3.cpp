#include "question3.h"
#include <iostream>
#include <chrono>
#include <thread>

int ATC::traffic = 0;

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
            std::cout << "Aircraft #" << myPlane << " requesting landing." << std::endl;
            air_traffic->addTraffic();
            air_traffic->airTrafficOrder.push(myPlane);
        }
        else if (!air_traffic->trafficNumber()) {
            std::cout << "Approach pattern full. Aircraft #" << myPlane << " redirected to another airport." << std::endl;
            hasLanded = true;
        }

        // Determines if the given plane is at the front of the approach order, if it is it and the ATC is not talking
        // to another pilot at the given time, it will land and the plane is removed from the queue.
        if (air_traffic->airTrafficOrder.front() && air_traffic->sleepStatus()) {
            air_traffic->changeSleepStatus();
            std::cout << "Airplane #" << myPlane << " is cleared for landing." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            hasLanded = true;

            std::cout << "Runway is clear." << std::endl;
            air_traffic->changeSleepStatus();
            air_traffic->airTrafficOrder.pop();
        }
    }   
}

