//
// Created by morei on 05/09/2020.
//

#include <cstdlib>
#include "InnerFeed23.h"

PlaneFuelSystem::InnerFeed23::InnerFeed23() {
    this->pumpStates = (bool*) malloc(21*sizeof(bool));
    this->valveStates = (bool*) malloc(40 * sizeof(bool));
    this->output = (bool**) malloc(2*sizeof(bool*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::InnerFeed23::~InnerFeed23() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

bool **PlaneFuelSystem::InnerFeed23::getTemplate(const int* tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = false;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = false;

    bool f4 = true; bool f5 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[4] > tanks[5] + 50) //if tank4 has more than tank5
        f4 = false;
    if (tanks[5] > tanks[4] + 50) //if tank5 has more than tank4
        f5 = false;

    if (!cases[1] && !cases[3] && !cases[7]) { //all normal, oh yes
        if (f4) this->valveStates[8] = true;
        if (f5) this->valveStates[10] = true;
        this->pumpStates[11] = true;
        this->pumpStates[13] = true;
        return this->output;
    }
    if ((cases[1] || cases[3]) && !cases[7] ) {//all transfers on aft or gallery swap for inner (uses aft)
        if (f4) this->valveStates[9] = true;
        if (f5) this->valveStates[11] = true;
        this->pumpStates[12] = true;
        this->pumpStates[14] = true;
        return this->output;
    }
    if (cases[7] && aut) {
        //Should not happen
        return nullptr;
    }

    return nullptr;
}