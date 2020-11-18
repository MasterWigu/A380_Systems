//
// Created by MasterWigu on 07/11/2020.
//


#include "ECAMFrontend.h"

namespace ECAM {
    ECAMFrontend::ECAMFrontend() {
        //GENERAL
        this->SDShownId = 0;

        //FUEL
        this->tankQuantities = (int*) malloc(15 * sizeof(int));
        for (int i=0; i<15; i++)
            this->tankQuantities[i] = 0;

        this->pmpStates = (int*) malloc(21 * sizeof(int));
        for (int i=0; i<15; i++)
            this->pmpStates[i] = 0;

    }


    //*************************** GENERAL ***************************
    int ECAMFrontend::getSdShownId() const {
        return SDShownId;
    }

    void ECAMFrontend::setSdShownId(int sdShownId) {
        SDShownId = sdShownId;
    }


    //*************************** FUEL ***************************
    void ECAMFrontend::setTankQuantities(int *tqs) {
        for (int i=0; i<15; i++)
            this->tankQuantities[i] = tqs[i];
    }

    void ECAMFrontend::getTankQuantities(int *out) {
        for (int i=0; i<15; i++)
            out[i] = this->tankQuantities[i];
    }

    void ECAMFrontend::setPmpStates(int *pss) {
        for (int i=0; i<21; i++)
            this->pmpStates[i] = pss[i];
    }

    void ECAMFrontend::getPmpStates(int *out) {
        for (int i=0; i<21; i++)
            out[i] = this->pmpStates[i];
    }
}