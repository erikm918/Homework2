#include "question1-2-3-4.h"

void Question3() {
    // Constant numbers required for the code to operate.
    const int trafficPatternNumber = 3;
    const int numOfPilots = 10;

    // Creates ATC and vector to contain threads and pilots
    AirTrafficController atc;
    std::vector<std::thread> all_threads;
    std::vector<std::shared_ptr<Pilot>> pilots;

    // Creates necessary pilots and puts them in the back of a vector.
    for (int i = 0; i < numOfPilots; i++) {
        pilots.emplace_back(std::make_shared<Pilot>());
    }

    std::mutex m1, m2, speakMtx;

    auto startTime = std::chrono::high_resolution_clock::now();

    /* 
    Forces the first pilot in the pilots vector into the pattern such that it may immediately begen landing process.
    Primarily here to prevent weird order of output and ensure that results are as expected. Doesn't effect anything
    else in the code
    */
    pilots[0]->setPattern();
    pilots[0]->enterPattern();

    static unsigned int inPattern = 0;

    // While loop that runs on the condition that the whole vector is not finished landing yet. This include diversions.
    while (std::all_of(pilots.begin(), pilots.end(), [] (const auto& pilot) {return pilot->hasLanded();}) == false) {
        for (auto& p : pilots) {

            // Ignores pilots that have already landed
            if (!p->hasLanded()) {
                /* 
                    Creates and adds thread to the all_threads vector. This allows for multiple tasks to be completed
                    at the same time. Use of a lambda function in order to determine the correct steps required by 
                    the pilot and ATC.
                */
                all_threads.emplace_back([&]() {
                    // Determines if the pilot can join the pattern or not. If pattern is full the plane is diverted 
                    // and considered landed.
                    // Determines if the pilot can communicate with the ATC. If it can, and other required cases are met,
                    // the pilot will land the plane and will be ignored in the future.
                    if (p->isInPattern() && atc.isAsleep() && m2.try_lock() && !p->hasLanded()) {
                        atc.communicate();

                        p->landPlane();

                        if (inPattern > 0) {
                            inPattern -= 1;
                        }

                        atc.fallAsleep();
                        m2.unlock();
                    }

                    if (m1.try_lock()) {
                        if (inPattern < 3 && !p->isInPattern() && !p->hasLanded()) {
                            inPattern += 1;
                            p->enterPattern();
                        }
                        else if (inPattern >=3 && !p->isInPattern() && !p->hasLanded()) {
                            p->divertPilot();
                        }

                        m1.unlock();
                    }
                });
            }
        }
    }

    // Ensures all created threads are ended.
    for (auto& t : all_threads) {
        t.join();
    }

    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stopTime - startTime);

    std::cout << "Total duration of landing procedure: " << duration.count() << " seconds" <<std::endl;
}