//
// Created by morei on 01/09/2020.
//

#ifndef A380_SYSTEMS_FQMS_H
#define A380_SYSTEMS_FQMS_H

#include <cstdlib>
#include <cmath>
#include "../PhysicalFuelSystem/FuelSystem.h"
#include "../FuelSystemFrontend.h"
#include "FQDC.h"
#include "Templates/TemplateGetter.h"

namespace PlaneFuelSystem {
    class FQMS {
    private:
        int* feedTks;

        PhysicalFuelSystem::FuelSystem* fuelSystem;
        PlaneFuelSystem::FQDC* fqdc;
        FuelSystem::FuelSystemFrontend* frontend;

        PlaneFuelSystem::TemplateGetter* templates;

        bool fwdOccupied;
        bool aftOccupied;

        bool* abnCases;

        int* tankLevels;

        int* commandedVlvStates;
        bool* commandedPumpStates;

        int* vlvsFailStates;
        int* pumpsFailStates;
        bool* pumpsCockpitButtons;
        bool* xfrCockpitButtons;
        bool* crossFeedCockpit;
        bool emergValvesCockpit;

        bool* requestedLPValves;

        bool* commandedTransfers;
        bool* lastTransfers;

        bool* ECAMProceduresNow;
        bool* ECAMProceduresPrevious;

        bool inFlight;
        int FOB;
        double CGTarget;
        int FL;
        float simTime;
        float lastSimTime;

        bool flWasAbove255;
        double time80min;
        double time30min;
        double timeAbvFL255;
        double timeBlwFL245;

        int* gravVlvsAux;

        void arraysInit();

        void getTankLevels();

        void updateCGTarget(int GW);
        void updateTimers(int remMinutes, int f);
        void detectAbnCases();

        void selectTransfers(int remFltTime, double currCG);
        void selectNormalTransfers(int remTimeMins, double currCG);
        void applyTransfers();
        void applyState();
        void applyPumpState();
        void applyValveState();

        void reportECAMProc();
        void processPmpFailuresECAM(int id);

    public:
        FQMS(PhysicalFuelSystem::FuelSystem *fS, FQDC *f, FuelSystem::FuelSystemFrontend* sFE);

        void updateLoop(int remMinutes, int GW, double currCG, float simulatorTime, int FL);



        int getPumpStateECAM(int id);

        int getCrossfeedVlvsStateECAM(int id);

        int getEngLPStateECAM(int id);

        int getAPUFeedStateECAM();

        int getTrimVlvStateECAM();

        int getTransferVlvsStateECAM(int id);

        int getGravVlvsStateECAM(int id);

        int getEmergVlvStateECAM(int id);

        void processCumulativeECAMProc();
    };
}

#endif //A380_SYSTEMS_FQMS_H
