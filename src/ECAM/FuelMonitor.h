//
// Created by MasterWigu on 07/11/2020.
//

#ifndef A380_SYSTEMS_FUELMONITOR_H
#define A380_SYSTEMS_FUELMONITOR_H

#include <cstdlib>
#include "../PluginControl/PlaneSystemsFrontends.h"
#include "ECAMDataCache.h"

namespace ECAM {
    class FuelMonitor {
    private:
        int* gravVlvsAux;
        PluginControl::PlaneSystemsFrontends* planeSysFe;
        ECAMDataCache* ecamDataCache;

        bool* tempPmpsBtns;
        bool* tempLPSts;


        int getPumpStateECAM(int id);
        int getCrossfeedVlvsStateECAM(int id);
        int getEngLPStateECAM(int id);
        int getAPUFeedStateECAM();
        int getTrimVlvStateECAM();
        int getTransferVlvsStateECAM(int id);
        int getGravVlvsStateECAM(int id);
        int getEmergVlvStateECAM(int id);
    public:
        explicit FuelMonitor(ECAMDataCache* edc);
        void setSystemsFEs(PluginControl::PlaneSystemsFrontends* pfe);

        void updateFrontend();


    };
}


#endif //A380_SYSTEMS_FUELMONITOR_H
