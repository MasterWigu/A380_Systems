//
// Created by morei on 05/09/2020.
//

#include <cstdlib>
#include "InnerFeed14.h"

PlaneFuelSystem::InnerFeed14::InnerFeed14() {
    this->pumpStates = (bool*) malloc(21*sizeof(bool));
    this->valveStates = (bool*) malloc(40 * sizeof(bool));
    this->output = (bool**) malloc(2*sizeof(bool*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::InnerFeed14::~InnerFeed14() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

bool **PlaneFuelSystem::InnerFeed14::getTemplate(const int* tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = false;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = false;

    bool f1 = true; bool f8 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[1] > tanks[8] + 50) //if tank1 has more than tank8
        f1 = false;
    if (tanks[8] > tanks[1] + 50) //if tank1 has more than tank8
        f8 = false;

    if (!cases[2] && !cases[3] && !cases[7]) { //all normal, oh yes
        if (f1) this->valveStates[2] = true;
        if (f8) this->valveStates[16] = true;
        this->pumpStates[11] = true;
        this->pumpStates[13] = true;
        return this->output;
    }
    if ((cases[2] || cases[3]) && !cases[7] ) {//all transfers on aft or gallery swap for inner (uses aft)
        if (f1) this->valveStates[3] = true;
        if (f8) this->valveStates[17] = true;
        this->pumpStates[12] = true;
        this->pumpStates[14] = true;
        return this->output;
    }
    if (cases[7] && aut) {
        //TODO failure
        return this->output;
    }

    //TODO manual mode


    return this->output;
}