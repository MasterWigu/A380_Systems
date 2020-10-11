//
// Created by morei on 05/09/2020.
//

#include <cstdlib>
#include "MidFeed14.h"

PlaneFuelSystem::MidFeed14::MidFeed14() {
    this->pumpStates = (int*) malloc(21*sizeof(int));
    this->valveStates = (int*) malloc(40 * sizeof(int));
    this->output = (int**) malloc(2*sizeof(int*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::MidFeed14::~MidFeed14() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

int **PlaneFuelSystem::MidFeed14::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = 0;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = 0;

    bool f1 = true; bool f8 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[1] > tanks[8] + 50) //if tank1 has more than tank8
        f1 = false;
    if (tanks[8] > tanks[1] + 50) //if tank1 has more than tank8
        f8 = false;

    if (!cases[1] && !cases[4] && !cases[7]) { //all normal, oh yes
        if (f1) this->valveStates[2] = 1;
        if (f8) this->valveStates[16] = 1;
        this->pumpStates[9] = 1;
        this->pumpStates[15] = 1;
        return this->output;
    }
    if ((cases[1] || cases[4]) && !cases[7] ) {//all transfers on aft or gallery swap for mid (uses aft)
        if (f1) this->valveStates[3] = 1;
        if (f8) this->valveStates[17] = 1;
        this->pumpStates[10] = 1;
        this->pumpStates[16] = 1;
        return this->output;
    }
    if (cases[7] && aut) {
        //Should not happen
        return nullptr;
    }

    return nullptr;
}