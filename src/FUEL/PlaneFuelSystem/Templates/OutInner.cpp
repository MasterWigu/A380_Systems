//
// Created by MasterWigu on 08/09/2020.
//

#include "OutInner.h"
#include <cstdlib>

PlaneFuelSystem::OutInner::OutInner() {
    this->pumpStates = (int*) malloc(21*sizeof(int));
    this->valveStates = (int*) malloc(40 * sizeof(int));
    this->output = (int**) malloc(2*sizeof(int*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::OutInner::~OutInner() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

int **PlaneFuelSystem::OutInner::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = 0;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = 0;

    bool f3 = true; bool f6 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[3] > tanks[6] + 50) //if tank3 has more than tank6
        f3 = false;
    if (tanks[6] > tanks[3] + 50) //if tank6 has more than tank3
        f6 = false;

    if (!cases[1] && !cases[5] && !cases[7]) { //all normal, oh yes (fwd)
        if (f3) this->valveStates[6] = 1;
        if (f6) this->valveStates[12] = 1;
        this->pumpStates[8] = 1;
        this->pumpStates[17] = 1;
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
