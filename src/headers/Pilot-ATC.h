#ifndef AIRTRAFFIC
#define AIRTRAFFIC

#include <memory>
#include <queue>
#include <mutex>

class AirTrafficController {
    bool asleep;
    std::mutex atcMtx;

    public:
        AirTrafficController() : asleep(true) {}

        void communicate();
        void fallAsleep();
        bool isAsleep();
};

class Pilot {
    bool inPattern;
    bool landed;
    static std::mutex pilotMtx;

    int myID;
    static int genID;

    public:
        Pilot() : inPattern(false) {myID = genID; genID++;}

        int getID() {return this->myID;}
        bool isInPattern() {return this->inPattern;}
        bool hasLanded() {return this->landed;}
        void landPlane();
        void setLanding() {landed = true;}
        void setPattern() {inPattern = true;}
        void enterPattern();
        void divertPilot();
};

#endif