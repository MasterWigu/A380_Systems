//
// Created by MasterWigu on 05/09/2020.
//

#include <cstdlib>
#include "MidFeed23.h"

PlaneFuelSystem::MidFeed23::MidFeed23() {
    this->pumpStates = (int*) malloc(21*sizeof(int));
    this->valveStates = (int*) malloc(40 * sizeof(int));
    this->output = (int**) malloc(2*sizeof(int*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::MidFeed23::~MidFeed23() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

int **PlaneFuelSystem::MidFeed23::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = 0;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = 0;

    bool f4 = true; bool f5 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[4] > tanks[5] + 50) //if tank4 has more than tank5
        f4 = false;
    if (tanks[5] > tanks[4] + 50) //if tank5 has more than tank4
        f5 = false;

    if (!cases[1] && !cases[4] && !cases[7]) { //all normal, oh yes
        if (f4) this->valveStates[8] = 1;
        if (f5) this->valveStates[10] = 1;
        this->pumpStates[9] = 1;
        this->pumpStates[15] = 1;
        return this->output;
    }
    if ((cases[1] || cases[4]) && !cases[7] ) {//all transfers on aft or gallery swap for mid (uses aft)
        if (f4) this->valveStates[9] = 1;
        if (f5) this->valveStates[11] = 1;
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