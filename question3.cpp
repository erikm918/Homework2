#include "question3.h"
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>

void Question3() {
    const int trafficPatternNumber = 3;
    const int numOfPilots = 10;

    AirTrafficControler atc;
    std::vector<std::thread> all_threads;
    std::vector<std::shared_ptr<Pilot>> pilots;

    // Creates necessary pilots and puts them in the back of a vector.
    for (int i = 0; i < numOfPilots; i++) {
        pilots.emplace_back(std::make_shared<Pilot>());
    }

    std::mutex m1, m2;

    auto startTime = std::chrono::high_resolution_clock::now();

    static int inPattern = 0;

    while (std::all_of(pilots.begin(), pilots.end(), [] (const auto& pilot) {return pilot->hasLanded();}) == false) {
        for (auto& p : pilots) {

            all_threads.emplace_back([&]() {
                if (m1.try_lock()) {
                    if (inPattern <= 3 && !p->isInPattern() && !p->hasLanded()) {
                        inPattern += 1;
                        p->enterPattern();
                    }
                    else if (inPattern > 3 && !p->isInPattern() && !p->hasLanded()) {
                        std::cout << "Traffic pattern is full. Diverting Pilot " << p->getID() 
                                                                        << " to another airport." << std::endl;
                        p->setLanding();
                    }

                    m1.unlock();
                }
                
                if (p->isInPattern() && atc.isAsleep() && m2.try_lock()) {
                    atc.communicate();
                    std::cout << "Pilot " << p->getID() << " has requested landing." << std::endl;

                    p->landPlane();
                    
                    atc.fallAsleep();

                    p->leavePattern();
                    inPattern -= 1;
                    m2.unlock();
                }
            });
        }
    }

    for (auto& t : all_threads) {
        t.join();
    }

    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stopTime - startTime);

    std::cout << "Total duration of landing procedure: " << duration.count() << " seconds" <<std::endl;
}