#ifndef AIRTRAFFIC
#define AIRTRAFFIC

#include <memory>
#include <queue>



class ATC {
    static int traffic;
    bool isAsleep = true;

    public:
        bool trafficNumber();
        bool sleepStatus() {return isAsleep;}
        void addTraffic();
        void changeSleepStatus();
        std::queue<int> airTrafficOrder;
};

class Pilot {
    bool inTraffic = false;
    static int planeNumber;
    int myPlane = 0;
    bool hasLanded = false; // This both includes at the given airport or if it was redirected.

    public:
        Pilot(); // Only exists to increase plane number for assignment.
        void attemptLand(std::shared_ptr<ATC> air_traffic);
        bool flightStatus() {return hasLanded;}
        int findPlane() {return myPlane;}
};

#endif