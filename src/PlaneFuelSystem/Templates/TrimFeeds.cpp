//
// Created by morei on 07/09/2020.
//


#include <cstdlib>
#include "TrimFeeds.h"

PlaneFuelSystem::TrimFeeds::TrimFeeds() {
    this->pumpStates = (int*) malloc(21*sizeof(int));
    this->valveStates = (int*) malloc(40 * sizeof(int));
    this->output = (int**) malloc(2*sizeof(int*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::TrimFeeds::~TrimFeeds() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

int **PlaneFuelSystem::TrimFeeds::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = 0;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = 0;

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

    //NOTE: Case 6 affects trim, but no change in template is needed (it is like normal)

    if (!cases[0] && !cases[7]) { //all normal, oh yes (aft)
        if (f1) this->valveStates[3] = 1;
        if (f4) this->valveStates[9] = 1;
        if (f5) this->valveStates[11] = 1;
        if (f8) this->valveStates[17] = 1;
        this->valveStates[38] = 1; //aft trim bus valve
        this->pumpStates[20] = 1;
        this->pumpStates[21] = 1;
        return this->output;
    }
    if (cases[0] && !cases[7]) {//case 1 - all trans on fwd
        if (f1) this->valveStates[2] = 1;
        if (f4) this->valveStates[8] = 1;
        if (f5) this->valveStates[10] = 1;
        if (f8) this->valveStates[16] = 1;
        this->valveStates[37] = 1; //fwd trim bus valve
        this->pumpStates[20] = 1;
        this->pumpStates[21] = 1;
        return this->output;
    }
    if (cases[7] && aut) {
        //when we have general failure, no automatic should happen
        return nullptr;
    }

    //this transfer is impossible in manual mode
    return nullptr;
}