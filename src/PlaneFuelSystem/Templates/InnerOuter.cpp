//
// Created by morei on 07/09/2020.
//

#include "InnerOuter.h"
#include <cstdlib>

PlaneFuelSystem::InnerOuter::InnerOuter() {
    this->pumpStates = (int*) malloc(21*sizeof(int));
    this->valveStates = (int*) malloc(40 * sizeof(int));
    this->output = (int**) malloc(2*sizeof(int*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::InnerOuter::~InnerOuter() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

int **PlaneFuelSystem::InnerOuter::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = 0;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = 0;

    bool f0 = true; bool f9 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[0] > tanks[9] + 50) //if tank0 has more than tank9
        f0 = false;
    if (tanks[9] > tanks[0] + 50) //if tank9 has more than tank0
        f9 = false;

    if (!cases[1] && !cases[2] && !cases[3] && !cases[7]) { //all normal, oh yes (fwd)
        if (f0) this->valveStates[0] = 1;
        if (f9) this->valveStates[18] = 1;
        this->pumpStates[11] = 1;
        this->pumpStates[13] = 1;
        return this->output;
    }
    if ((cases[1] || cases[2] || cases[3]) && !cases[7] ) {//all transfers on aft or gallery swap for inner or to outer in aft (uses aft)
        if (f0) this->valveStates[1] = 1;
        if (f9) this->valveStates[19] = 1;
        this->pumpStates[12] = 1;
        this->pumpStates[14] = 1;
        return this->output;
    }
    if (cases[7] && aut) {
        //Should not happen
        return nullptr;
    }

    return nullptr;
}
