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

        /// variable to store if the front gallery is in use
        bool fwdOccupied;

        /// variable to store if the aft gallery is in use
        bool aftOccupied;

        /// Abnormal cases as stated in the FCOM
        /// Case 4 is two cases, for mid or inner, that makes a total of 7 cases instead of 6 (+ 1 case for other combined failures)
        bool* abnCases;

        /// temp information about the tank levels
        int* tankLevels;


        int* commandedVlvStates;
        bool* commandedPumpStates;

        int* vlvsFailStates;
        int* pumpsFailStates;

        // cockpit buttons temp storage
        bool* pumpsCockpitButtons;
        bool* xfrCockpitButtons;
        bool* crossFeedCockpit;
        bool emergValvesCockpit;

        // info about if each of the LP valves should be open (controlled by the engines)
        bool* requestedLPValves;

        /// The transfers that should be happening in the current cycle (see transfer ids table)
        bool* commandedTransfers;

        /// Transfers that occurred in the last cycle
        bool* lastTransfers;

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

        /// Function to initialize all the arrays of the class
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

        void updateFrontend();

    public:
        FQMS(PhysicalFuelSystem::FuelSystem *fS, FQDC *f, FuelSystem::FuelSystemFrontend* sFE);

        void updateLoop(int remMinutes, int GW, double currCG, float simulatorTime, int FL);

    };
}

#endif //A380_SYSTEMS_FQMS_H
