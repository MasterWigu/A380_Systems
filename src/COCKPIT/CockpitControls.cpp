//
// Created by MasterWigu on 18/10/2020.
//

#include <cstdlib>
#include "CockpitControls.h"

namespace Cockpit {

    CockpitControls::CockpitControls() {
        this->fuelButtons = (int*) malloc(34*sizeof(int));
        for (int i = 0; i < 34; i++)
            this->fuelButtons[i] = 0;

        this->ecamButtons = (int*) malloc(34*sizeof(int));
        for (int i = 0; i < 34; i++)
            this->ecamButtons[i] = 0;
    }

    int *CockpitControls::getFuelButtons() {
        return this->fuelButtons;
    }

    void CockpitControls::setFuelButton(int id, int state) {
        this->fuelButtons[id] = state;
    }

    int *CockpitControls::getEcamButtons() {
        return this->ecamButtons;
    }

    void CockpitControls::setEcamButton(int id, int state) {
        this->ecamButtons[id] = state;
    }
}