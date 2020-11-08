//
// Created by morei on 07/11/2020.
//

#ifndef A380_SYSTEMS_ECAMDATACACHE_H
#define A380_SYSTEMS_ECAMDATACACHE_H

#include <cstdlib>

#include "../PluginControl/PlaneSystemsFrontends.h"

namespace ECAM {
    class ECAMDataCache {
    private:
        PluginControl::PlaneSystemsFrontends* planeSysFes;

        void updateFuelCache();

    public:
        ECAMDataCache();
        void setSystemsFrontends(PluginControl::PlaneSystemsFrontends* psf);
        void updateCache();

        int* FUELTkLevels;
        int* FUELVlvCommSts;
        int* FUELVlvFailSts;
        bool* FUELPmpCommSts;
        int* FUELPmpFailSts;
        bool* FUELPmpsBtns;
        bool* FUELLPSts;

    };
}


#endif //A380_SYSTEMS_ECAMDATACACHE_H
