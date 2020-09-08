//
// Created by morei on 08/09/2020.
//

#include "OutInner.h"
#include <cstdlib>

PlaneFuelSystem::OutInner::OutInner() {
    this->pumpStates = (bool*) malloc(21*sizeof(bool));
    this->valveStates = (bool*) malloc(40 * sizeof(bool));
    this->output = (bool**) malloc(2*sizeof(bool*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::OutInner::~OutInner() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

bool **PlaneFuelSystem::OutInner::getTemplate(const int* tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = false;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = false;

    bool f3 = true; bool f6 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[3] > tanks[6] + 50) //if tank3 has more than tank6
        f3 = false;
    if (tanks[6] > tanks[3] + 50) //if tank6 has more than tank3
        f6 = false;

    if (!cases[1] && !cases[5] && !cases[7]) { //all normal, oh yes (fwd)
        if (f3) this->valveStates[6] = true;
        if (f6) this->valveStates[12] = true;
        this->pumpStates[8] = true;
        this->pumpStates[17] = true;
        return this->output;
    }
    if ((cases[1] || cases[5]) && !cases[7] ) {//all transfers on aft or grav from outer (uses fwd)
        //We should never have transfers out->inner if case 2 or case 5 are active
        return nullptr;
    }
    if (cases[7] && aut) {
        //when we have general failure, no automatic should happen
        return nullptr;
    }

    if (cases[7] && !aut) {
        //Out->inner is impossible in manual mode, should never happen
        return nullptr;
    }

    return nullptr;
}
