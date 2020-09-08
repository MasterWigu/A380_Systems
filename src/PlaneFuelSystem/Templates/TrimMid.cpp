//
// Created by morei on 08/09/2020.
//

#include "TrimMid.h"
#include <cstdlib>

PlaneFuelSystem::TrimMid::TrimMid() {
    this->pumpStates = (bool*) malloc(21*sizeof(bool));
    this->valveStates = (bool*) malloc(40 * sizeof(bool));
    this->output = (bool**) malloc(2*sizeof(bool*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::TrimMid::~TrimMid() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

bool **PlaneFuelSystem::TrimMid::getTemplate(const int* tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = false;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = false;

    bool f2 = true; bool f7 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[2] > tanks[7] + 50) //if tank3 has more than tank6
        f2 = false;
    if (tanks[7] > tanks[2] + 50) //if tank6 has more than tank3
        f7 = false;

    if (!cases[0] && !cases[4] && !cases[7]) { //all normal, oh yes (aft)
        if (f2) this->valveStates[5] = true;
        if (f7) this->valveStates[15] = true;
        this->valveStates[38] = true; //aft trim bus valve
        this->pumpStates[18] = true;
        this->pumpStates[19] = true;
        return this->output;
    }
    if ((cases[0] || cases[4]) && !cases[7] ) {//all transfers on fwd or gallery swap for mid (uses fwd)
        if (f2) this->valveStates[4] = true;
        if (f7) this->valveStates[14] = true;
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
