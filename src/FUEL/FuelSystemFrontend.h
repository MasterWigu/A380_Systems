//
// Created by MasterWigu on 17/10/2020.
//

#ifndef A380_SYSTEMS_FUELSYSTEMFRONTEND_H
#define A380_SYSTEMS_FUELSYSTEMFRONTEND_H

#include <cstdlib>

namespace FuelSystem {
    class FuelSystemFrontend {
    private:
        int* tankLevels;
        int* valvesFailStates;
        int* valvesCommStates;
        int* pmpsFailStates;
        bool* pmpsCommStates;

    public:
        FuelSystemFrontend();

        void getTankLevels(int* out);
        void setTankLevels(int* levels);

        void getValvesFailStates(int* out);
        void setValvesFailStates(int *valvesFailStates);

        void getValvesCommStates(int* out);
        void setValvesCommStates(int *valvesCommStates);

        void getPmpsFailStates(int* out);
        void setPmpsFailStates(int *pmpsFailStates);

        void getPmpsCommStates(bool* out);
        void setPmpsCommStates(bool *pmpsCommStates);
    };
}


#endif //A380_SYSTEMS_FUELSYSTEMFRONTEND_H
