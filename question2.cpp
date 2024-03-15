#include "question2.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <vector>

void Question2() {
    // Question 2

    // Creates 5 tools.
    auto t1 = std::make_shared<Tools>();
    auto t2 = std::make_shared<Tools>();
    auto t3 = std::make_shared<Tools>();
    auto t4 = std::make_shared<Tools>();
    auto t5 = std::make_shared<Tools>();

    // Creates 5 robots with the proper tools attached to them
    std::shared_ptr<Robot> r1 = std::make_shared<Robot>(t1, t5);
    std::shared_ptr<Robot> r2 = std::make_shared<Robot>(t1, t2);
    std::shared_ptr<Robot> r3 = std::make_shared<Robot>(t2, t3);
    std::shared_ptr<Robot> r4 = std::make_shared<Robot>(t3, t4);
    std::shared_ptr<Robot> r5 = std::make_shared<Robot>(t4, t5);

    auto uncomplete_robots = {r1, r2, r3, r4, r5}; // List to check if all robots have done their task.

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> all_threads;

    while (std::all_of(uncomplete_robots.begin(), uncomplete_robots.end(), [](const auto& robot) 
                                                            {return robot->isComplete();}) == false) {
        for (auto& r : uncomplete_robots) {
            // Adds a robot completing its task to the the thread vector, then checks to see if all robots in the robot 
            // vector have completed their task. If this is true, the full loop ends.
            all_threads.emplace_back([&]() {
                r->completeTask();
            });

            // Prevents printing two different sets of text on the same line.
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); 
        }
    }

    for (auto& thread : all_threads) {
        thread.join();
    }

    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( stopTime - startTime );

    std::cout << "Total time to complete tasks: " << duration.count() << " seconds" <<std::endl;
}