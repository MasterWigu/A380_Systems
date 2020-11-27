#include <cstdlib>
#include "MidFeeds.h"

PlaneFuelSystem::MidFeeds::MidFeeds() {
    this->pumpStates = (int*) malloc(21*sizeof(int));
    this->valveStates = (int*) malloc(40 * sizeof(int));
    this->output = (int**) malloc(2*sizeof(int*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::MidFeeds::~MidFeeds() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

int **PlaneFuelSystem::MidFeeds::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = 0;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = 0;

    bool f1 = true; bool f8 = true;
    bool f4 = true; bool f5 = true;

    int vlvStates = aut ? 3 : 1; //if this is called in auto, valves are auto (1) else valves are manual (3)

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[4] > tanks[5] + 50 || tanks[4] > tanks[1] + 50 || tanks[4] > tanks[8] + 50 ) //if tank4 has more than one of others
        f4 = false;
    if (tanks[5] > tanks[4] + 50 || tanks[5] > tanks[1] + 50 || tanks[5] > tanks[8] + 50 ) //if tank5 has more than one of others
        f5 = false;
    if (tanks[1] > tanks[4] + 50 || tanks[1] > tanks[5] + 50 || tanks[1] > tanks[8] + 50 ) //if tank1 has more than one of others
        f1 = false;
    if (tanks[8] > tanks[1] + 50 || tanks[8] > tanks[4] + 50 || tanks[8] > tanks[5] + 50 ) //if tank8 has more than one of others
        f8 = false;

    if (!cases[2] && !cases[4] && !cases[7]) { //all normal, oh yes
        if (f1) this->valveStates[2] = vlvStates;
        if (f4) this->valveStates[8] = vlvStates;
        if (f5) this->valveStates[10] = vlvStates;
        if (f8) this->valveStates[16] = vlvStates;
        this->pumpStates[9] = 1;
        this->pumpStates[15] = 1;
        return this->output;
    }
    if ((cases[2] || cases[4]) && !cases[7] ) {//all transfers on aft or gallery swap for mid (uses aft)
        if (f1) this->valveStates[3] = vlvStates;
        if (f4) this->valveStates[9] = vlvStates;
        if (f5) this->valveStates[11] = vlvStates;
        if (f8) this->valveStates[17] = vlvStates;
        this->pumpStates[10] = 1;
        this->pumpStates[16] = 1;
        return this->output;
    }
    if (cases[7] && aut) {
        //should never happen
        return nullptr;
    }

    //TODO hell mode


    return nullptr;
}