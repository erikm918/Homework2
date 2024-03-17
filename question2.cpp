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

    /* 
        These mutexes prevent weird behavrios in the loop that completes the tasks. Without them, there are
        odd behaviors such as the code breaking into an infinite loop, 3 robots being able to complete a task
        at a time (there are a max of two that can complete at a time given the fact that there are five tools; 
        this means only two robots at a time can hold tools), etc.
    */
    std::mutex m1, m2;

    auto uncomplete_robots = {r1, r2, r3, r4, r5}; // List to check if all robots have done their task.

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> all_threads;

    while (std::all_of(uncomplete_robots.begin(), uncomplete_robots.end(), [](const auto& robot) 
                                                            {return robot->isComplete();}) == false) {
        for (auto& r : uncomplete_robots) {
            // Adds a robot completing its task to the the thread vector, then checks to see if all robots in the robot 
            // vector have completed their task. If this is true, the full loop ends.
            all_threads.emplace_back([&]() {
                if (m1.try_lock()) {
                    r->completeTask();
                    m1.unlock();
                }
                else if (m2.try_lock()) {
                    r->completeTask();
                    m2.unlock();
                }
            });
        }
    }

    // A for loop to join any threads created during the loop preventing amy issues with ending the task.
    for (auto& thread : all_threads) {
        thread.join();
    }

    // Determines the amount of time for all five robots to complete their tasks
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( stopTime - startTime );

    std::cout << "Total time to complete tasks: " << duration.count() << " seconds" <<std::endl;
}