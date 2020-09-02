//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELPUMP_H
#define UNTITLED_FUELPUMP_H
#include "FuelTank.h"


namespace FuelSystem{
    class FuelPump {
    private:
        int maxPumpRate = 0; //In kg/h
        int state = 0; // 0-Off, 1-On
        int commandedState;
        bool hasPower;
        bool isFailed;
        bool isFeed;

        FuelSystem::FuelTank* pumpLocation;

    public:
        FuelPump(FuelSystem::FuelTank* location, int rate, bool iF);
        int getPumpable();
        bool canPump();
        void pumpFuel(int amount);

        void setState(int s);
        int getState();

        void setPower(bool p);
        bool getPower();

        void setFailed(bool f);
        bool getFailed();

    };
}



#endif //UNTITLED_FUELPUMP_H
