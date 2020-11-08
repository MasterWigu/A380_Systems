//
// Created by morei on 17/10/2020.
//


#include "FuelSystemFrontend.h"

namespace FuelSystem {
    FuelSystemFrontend::FuelSystemFrontend() {
        this->tankLevels = (int*) malloc(15 * sizeof(int));
        for (int i=0; i<15; i++)
            this->tankLevels[i] = 0;

        this->valvesFailStates = (int*) malloc(47 * sizeof(int));
        for (int i=0; i<47; i++)
            this->valvesFailStates[i] = 0;
        this->valvesCommStates = (int*) malloc(47 * sizeof(int));
        for (int i=0; i<47; i++)
            this->valvesCommStates[i] = 0;

        this->pmpsFailStates = (int*) malloc(21 * sizeof(int));
        for (int i=0; i<21; i++)
            this->pmpsFailStates[i] = 0;
        this->pmpsCommStates = (bool*) malloc(21 * sizeof(bool));
        for (int i=0; i<21; i++)
            this->pmpsCommStates[i] = false;
    }


    void FuelSystemFrontend::getTankLevels(int* out) {
        for (int i=0; i<15; i++)
            out[i] = this->tankLevels[i];
    }

    void FuelSystemFrontend::setTankLevels(int *levels) {
        for (int i=0; i<15; i++)
            this->tankLevels[i] = levels[i];
    }

    void FuelSystemFrontend::getValvesFailStates(int *out) {
        for (int i=0; i<47; i++)
            out[i] = this->valvesFailStates[i];
    }

    void FuelSystemFrontend::setValvesFailStates(int *vfs) {
        for (int i=0; i<47; i++)
            this->valvesFailStates[i] = vfs[i];
    }

    void FuelSystemFrontend::getValvesCommStates(int *out) {
        for (int i=0; i<47; i++)
            out[i] = this->valvesCommStates[i];
    }

    void FuelSystemFrontend::setValvesCommStates(int *vcs) {
        for (int i=0; i<47; i++)
            this->valvesCommStates[i] = vcs[i];
    }

    void FuelSystemFrontend::getPmpsFailStates(int* out) {
        for (int i=0; i<21; i++)
            out[i] = this->pmpsFailStates[i];
    }

    void FuelSystemFrontend::setPmpsFailStates(int *pfs) {
        for (int i=0; i<21; i++)
            this->pmpsFailStates[i] = pfs[i];
    }

    void FuelSystemFrontend::getPmpsCommStates(bool* out) {
        for (int i=0; i<21; i++)
            out[i] = this->pmpsCommStates[i];
    }

    void FuelSystemFrontend::setPmpsCommStates(bool *pcs) {
        for (int i=0; i<21; i++)
            this->pmpsCommStates[i] = pcs[i];
    }

}