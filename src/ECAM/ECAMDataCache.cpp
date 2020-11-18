//
// Created by MasterWigu on 07/11/2020.
//

#include "ECAMDataCache.h"

namespace ECAM {

    ECAMDataCache::ECAMDataCache() {


        //***************************** FUEL *****************************
        this->FUELTkLevels = (int*) malloc(15*sizeof(int));
        this->FUELVlvCommSts = (int*) malloc(47*sizeof(int));
        this->FUELVlvFailSts = (int*) malloc(47*sizeof(int));
        this->FUELPmpCommSts = (bool*) malloc(21*sizeof(bool));
        this->FUELPmpFailSts = (int*) malloc(21*sizeof(int));

    }

    void ECAMDataCache::setSystemsFrontends(PluginControl::PlaneSystemsFrontends* psf) {
        this->planeSysFes = psf;
    }

    void ECAMDataCache::updateCache() {
        updateFuelCache();
    }

    void ECAMDataCache::updateFuelCache() {
        this->planeSysFes->fuelSystemFe->getTankLevels(this->FUELTkLevels);
        this->planeSysFes->fuelSystemFe->getValvesCommStates(this->FUELVlvCommSts);
        this->planeSysFes->fuelSystemFe->getValvesFailStates(this->FUELVlvFailSts);
        this->planeSysFes->fuelSystemFe->getPmpsCommStates(this->FUELPmpCommSts);
        this->planeSysFes->fuelSystemFe->getPmpsFailStates(this->FUELPmpFailSts);
    }


}