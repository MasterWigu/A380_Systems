//
// Created by morei on 08/09/2020.
//

#include "MidOuter.h"
#include <cstdlib>

PlaneFuelSystem::MidOuter::MidOuter() {
    this->pumpStates = (bool*) malloc(21*sizeof(bool));
    this->valveStates = (bool*) malloc(40 * sizeof(bool));
    this->output = (bool**) malloc(2*sizeof(bool*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::MidOuter::~MidOuter() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

bool **PlaneFuelSystem::MidOuter::getTemplate(const int* tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = false;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = false;

    bool f0 = true; bool f9 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[0] > tanks[9] + 50) //if tank0 has more than tank9
        f0 = false;
    if (tanks[9] > tanks[0] + 50) //if tank9 has more than tank0
        f9 = false;

    if (!cases[1] && !cases[2] && !cases[4] && !cases[7]) { //all normal, oh yes (fwd)
        if (f0) this->valveStates[0] = true;
        if (f9) this->valveStates[18] = true;
        this->pumpStates[9] = true;
        this->pumpStates[15] = true;
        return this->output;
    }
    if ((cases[1] || cases[2] || cases[4]) && !cases[7] ) {//all transfers on aft or gallery swap for mid or to outer in aft (uses aft)
        if (f0) this->valveStates[1] = true;
        if (f9) this->valveStates[19] = true;
        this->pumpStates[10] = true;
        this->pumpStates[16] = true;
        return this->output;
    }
    if (cases[7] && aut) {
        //Should not happen
        return nullptr;
    }

    return nullptr;
 }
