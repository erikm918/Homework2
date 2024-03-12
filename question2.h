#ifndef ROBOT
#define ROBOT

#include <memory>

class Tools {
    bool inUse = false;

    public:
        void setUse();
        bool checkIfUsed() {return inUse;}
};

class Robot {
    bool hasTools = false;
    bool myTask = false;

    static int serialNum;
    int mySerial = 0;
    
    std::shared_ptr<Tools> myTool1;
    std::shared_ptr<Tools> myTool2;

    public:
        Robot(std::shared_ptr<Tools> t1, std::shared_ptr<Tools> t2);
        void completeTask();
        bool isComplete() {return myTask;}
};

#endif