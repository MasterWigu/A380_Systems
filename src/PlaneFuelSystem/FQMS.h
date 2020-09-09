//
// Created by morei on 01/09/2020.
//

#ifndef A380_SYSTEMS_FQMS_H
#define A380_SYSTEMS_FQMS_H

#include "../FuelSystem/FuelSystem.h"
#include "FQDC.h"

namespace PlaneFuelSystem {
    class FQMS {
    private:
        int* feedTks;

        FuelSystem::FuelSystem* fuelSystem;
        PlaneFuelSystem::FQDC* fqdc;

        bool fwdOccupied;
        bool aftOccupied;

        bool* mainTransferDest;
        bool* mainTransferSrc;

        bool* abnCases;

        int* tankLevels;

        bool* commandedVlvStates;
        bool* commandedPumpStates;

        int* vlvsFailStates;
        int* pumpsFailStates;
        int* consValvesFailStates;
        bool* pumpsCockpitButtons;
        bool* xfrCockpitButtons;
        bool* crossFeedCockpit;
        bool emergValvesCockpit;

        bool* commandedTransfers;
        bool* lastTransfers;

        bool inFlight;
        int FOB;
        double CGTarget;

        void arraysInit();

        void pumpStatusCheck();
        void vlvStatusCheck();
        void getTankLevels();

        void updateCGTarget(int GW);
        void detectAbnCases();

        void selectTransfers(int remFltTime, double currCG);
        void selectNormalTransfers(int remTimeMins, double currCG);

        void applyState();
        void applyPumpState();
        void applyValveState();

    public:
        FQMS(FuelSystem::FuelSystem *fS, FQDC *f);

        void updateLoop(int remMinutes, int GW, double currCG);
    };
}

#endif //A380_SYSTEMS_FQMS_H
