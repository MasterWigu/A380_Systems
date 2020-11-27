#include <cstdlib>
#include "InnerFeeds.h"

PlaneFuelSystem::InnerFeeds::InnerFeeds() {
    this->pumpStates = (int*) malloc(21*sizeof(int));
    this->valveStates = (int*) malloc(40 * sizeof(int));
    this->output = (int**) malloc(2*sizeof(int*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::InnerFeeds::~InnerFeeds() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

int **PlaneFuelSystem::InnerFeeds::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual) {
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

    if (aut) {
        //this mode should never be called in automatic
        return nullptr;
    }

    if (!cases[2] && !cases[3] && !cases[7]) { //all normal, oh yes
        if (f1) this->valveStates[2] = 3;
        if (f4) this->valveStates[8] = 3;
        if (f5) this->valveStates[10] = 3;
        if (f8) this->valveStates[16] = 3;
        this->pumpStates[9] = 1;
        this->pumpStates[15] = 1;
        return this->output;
    }
    if ((cases[2] || cases[3]) && !cases[7] ) {//all transfers on aft or gallery swap for inner (uses aft)
        if (f1) this->valveStates[3] = 3;
        if (f4) this->valveStates[9] = 3;
        if (f5) this->valveStates[11] = 3;
        if (f8) this->valveStates[17] = 3;
        this->pumpStates[10] = 1;
        this->pumpStates[16] = 1;
        return this->output;
    }

    //TODO hell broke loose mode


    return nullptr;
}