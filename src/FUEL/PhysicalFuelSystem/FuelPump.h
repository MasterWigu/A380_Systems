//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELPUMP_H
#define UNTITLED_FUELPUMP_H
#include "FuelTank.h"


namespace PhysicalFuelSystem{
    class FuelPump {
    private:
        double maxPumpRate = 0; //In kg/h
        int state = 0; // 0-Off, 1-On
        int commandedState;
        bool hasPower;
        bool isFailed;
        bool isFeed;

        PhysicalFuelSystem::FuelTank* pumpLocation;

    public:
        FuelPump(PhysicalFuelSystem::FuelTank* location, int rate, bool iF);
        double getPumpable(float deltaTime);
        bool canPump();
        void pumpFuel(double amount);

        void setState(int s);
        int getState();

        void setPower(bool p);
        bool getPower();

        void setFailed(bool f);
        bool getFailed();

    };
}



#endif //UNTITLED_FUELPUMP_H
