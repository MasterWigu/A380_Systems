//
// Created by morei on 08/09/2020.
//

#include "TrimInner.h"
#include <cstdlib>

PlaneFuelSystem::TrimInner::TrimInner() {
    this->pumpStates = (bool*) malloc(21*sizeof(bool));
    this->valveStates = (bool*) malloc(40 * sizeof(bool));
    this->output = (bool**) malloc(2*sizeof(bool*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::TrimInner::~TrimInner() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

bool **PlaneFuelSystem::TrimInner::getTemplate(const int* tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = false;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = false;

    bool f3 = true; bool f6 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[3] > tanks[6] + 50) //if tank3 has more than tank6
        f3 = false;
    if (tanks[6] > tanks[3] + 50) //if tank6 has more than tank3
        f6 = false;

    if (!cases[0] && !cases[3] && !cases[7]) { //all normal, oh yes (aft)
        if (f3) this->valveStates[7] = true;
        if (f6) this->valveStates[13] = true;
        this->valveStates[38] = true; //aft trim bus valve
        this->pumpStates[18] = true;
        this->pumpStates[19] = true;
        return this->output;
    }
    if ((cases[0] || cases[3]) && !cases[7] ) {//all transfers on fwd or gallery swap for inner (uses fwd)
        if (f3) this->valveStates[6] = true;
        if (f6) this->valveStates[12] = true;
        this->valveStates[37] = true; //fwd trim bus valve
        this->pumpStates[18] = true;
        this->pumpStates[19] = true;
        return this->output;
    }
    if (cases[7] && aut) {
        //TODO failure
        return this->output;
    }

    //TODO manual mode


    return this->output;
}
