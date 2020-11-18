//
// Created by MasterWigu on 08/09/2020.
//

#include "TrimMid.h"
#include <cstdlib>

PlaneFuelSystem::TrimMid::TrimMid() {
    this->pumpStates = (int*) malloc(21*sizeof(int));
    this->valveStates = (int*) malloc(40 * sizeof(int));
    this->output = (int**) malloc(2*sizeof(int*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::TrimMid::~TrimMid() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

int **PlaneFuelSystem::TrimMid::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = 0;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = 0;

    bool f2 = true; bool f7 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[2] > tanks[7] + 50) //if tank3 has more than tank6
        f2 = false;
    if (tanks[7] > tanks[2] + 50) //if tank6 has more than tank3
        f7 = false;

    if (!cases[0] && !cases[4] && !cases[7]) { //all normal, oh yes (aft)
        if (f2) this->valveStates[5] = 1;
        if (f7) this->valveStates[15] = 1;
        this->valveStates[38] = 1; //aft trim bus valve
        this->pumpStates[18] = 1;
        this->pumpStates[19] = 1;
        return this->output;
    }
    if ((cases[0] || cases[4]) && !cases[7] ) {//all transfers on fwd or gallery swap for mid (uses fwd)
        if (f2) this->valveStates[4] = 1;
        if (f7) this->valveStates[14] = 1;
        this->valveStates[37] = 1; //fwd trim bus valve
        this->pumpStates[18] = 1;
        this->pumpStates[19] = 1;
        return this->output;
    }
    if (cases[7] && aut) {
        //when we have general failure, no automatic should happen
        return nullptr;
    }

    //this transfer is impossible in manual mode
    return nullptr;
}
