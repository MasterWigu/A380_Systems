//
// Created by morei on 08/09/2020.
//

#include <cstdlib>
#include "InnerFeeds.h"

PlaneFuelSystem::InnerFeeds::InnerFeeds() {
    this->pumpStates = (bool*) malloc(21*sizeof(bool));
    this->valveStates = (bool*) malloc(40 * sizeof(bool));
    this->output = (bool**) malloc(2*sizeof(bool*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::InnerFeeds::~InnerFeeds() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

bool **PlaneFuelSystem::InnerFeeds::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = false;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = false;

    bool f1 = true; bool f8 = true;
    bool f4 = true; bool f5 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[4] > tanks[5] + 50 || tanks[4] > tanks[1] + 50 || tanks[4] > tanks[8] + 50 ) //if tank4 has more than one of others
        f4 = false;
    if (tanks[5] > tanks[4] + 50 || tanks[5] > tanks[1] + 50 || tanks[5] > tanks[8] + 50 ) //if tank5 has more than one of others
        f5 = false;
    if (tanks[1] > tanks[4] + 50 || tanks[1] > tanks[5] + 50 || tanks[1] > tanks[8] + 50 ) //if tank1 has more than one of others
        f1 = false;
    if (tanks[8] > tanks[1] + 50 || tanks[8] > tanks[4] + 50 || tanks[8] > tanks[5] + 50 ) //if tank8 has more than one of others
        f8 = false;

    if (aut) {
        //this mode should never be called in automatic
        return nullptr;
    }

    if (!cases[2] && !cases[3] && !cases[7]) { //all normal, oh yes
        if (f1) this->valveStates[2] = true;
        if (f4) this->valveStates[8] = true;
        if (f5) this->valveStates[10] = true;
        if (f8) this->valveStates[16] = true;
        this->pumpStates[9] = true;
        this->pumpStates[15] = true;
        return this->output;
    }
    if ((cases[2] || cases[3]) && !cases[7] ) {//all transfers on aft or gallery swap for inner (uses aft)
        if (f1) this->valveStates[3] = true;
        if (f4) this->valveStates[9] = true;
        if (f5) this->valveStates[11] = true;
        if (f8) this->valveStates[17] = true;
        this->pumpStates[10] = true;
        this->pumpStates[16] = true;
        return this->output;
    }

    //TODO hell broke loose mode


    return nullptr;
}