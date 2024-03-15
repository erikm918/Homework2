#include "question3.h"
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>

void Question3() {
    // Question 3

    // Pilot p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;
    auto p1 = std::make_shared<Pilot>();
    auto p2 = std::make_shared<Pilot>();
    auto p3 = std::make_shared<Pilot>();
    auto p4 = std::make_shared<Pilot>();
    auto p5 = std::make_shared<Pilot>();
    auto p6 = std::make_shared<Pilot>();
    auto p7 = std::make_shared<Pilot>();
    auto p8 = std::make_shared<Pilot>();
    auto p9 = std::make_shared<Pilot>();
    auto p10 = std::make_shared<Pilot>();

    auto airTrafficControl = std::make_shared<ATC>();
    std::vector<std::shared_ptr<Pilot>> pilotList = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10};

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> atc_threads;

    bool allPilotsLanded = false;
    
    while (std::all_of(pilotList.begin(), pilotList.end(), [](const auto& pilot) 
                                                                    {return pilot->flightStatus();}) == false) {
        for (auto& p : pilotList) {
            atc_threads.emplace_back([&]() {
                p->attemptLand(airTrafficControl);
            });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    for (auto& thread : atc_threads) {
        thread.join();
    }

    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stopTime - startTime);

    std::cout << "Total time to complete tasks: " << duration.count() << " seconds" <<std::endl;
}