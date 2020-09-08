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
        int threshold14;
        int threshold23;
        int* feedTks;

        FuelSystem::FuelSystem* fuelSystem;
        PlaneFuelSystem::FQDC* fqdc;

        int fwdTransferInProgress;
        int aftTransferInProgress;

        bool* mainTransferDest;
        bool* mainTransferSrc;

        bool* abnCases;

        int* tankLevels;

        bool* commandedVlvStates;
        bool* commandedPumpStates;

        int* vlvsFailStates;
        int* pumpsFailStates;
        bool* pumpsCockpitButtons;
        bool* xfrCockpitButtons;
        bool* crossFeedCockpit;
        bool emergValvesCockpit;

        bool* commandedAutoTransfers;
        bool* commandedManualTransfers;

        void arraysInit();

        void pumpStatusCheck();
        void vlvStatusCheck();

        void getTankLevels();
        void updateThresholds(int remainMinutes);
        void checkMainTStart();
        void checkMainTStop();
        void checkMainTransfers(int remMinutes);

    public:
        FQMS(FuelSystem::FuelSystem *fS, FQDC *f);

        void updateLoop(int remMinutes);

        void applyState();

        void applyPumpState();

        void applyValveState();

        void detectAbnCases();
    };
}

#endif //A380_SYSTEMS_FQMS_H
