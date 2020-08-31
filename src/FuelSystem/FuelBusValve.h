//
// Created by morei on 28/08/2020.
//

#ifndef UNTITLED_FUELBUSVALVE_H
#define UNTITLED_FUELBUSVALVE_H


namespace FuelSystem {
    class FuelBus;

    class FuelBusValve {
    private:
        int state = 0; // 0=Closed, 1=Opened

        FuelSystem::FuelBus* bus1;
        FuelSystem::FuelBus* bus2;
    public:
        FuelBusValve(FuelSystem::FuelBus *location1, FuelSystem::FuelBus *location2);
        void setState(int nState);
        int getState();

        FuelBus* getLocation1();
        FuelBus* getLocation2();
    };
}

#endif //UNTITLED_FUELBUSVALVE_H
