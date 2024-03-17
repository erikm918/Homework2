#ifndef AIRTRAFFIC
#define AIRTRAFFIC

#include <memory>
#include <queue>
#include <mutex>

class AirTrafficControler {
    bool asleep;
    std::mutex atcMtx;

    public:
        AirTrafficControler() : asleep(true) {}

        void communicate();
        void fallAsleep();
        bool isAsleep();
};

class Pilot {
    bool inPattern;
    bool landed;
    std::mutex pilotMtx;

    int myID;
    static int genID;

    public:
        Pilot() : inPattern(false) {myID = genID; genID++;}

        int getID() {return this->myID;}
        bool isInPattern() {return this->inPattern;}
        bool hasLanded() {return this->landed;}
        void enterPattern();
        void leavePattern();
        void landPlane();
        void setLanding() {landed = true;}
};

#endif