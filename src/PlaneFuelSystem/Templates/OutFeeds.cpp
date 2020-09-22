//
// Created by morei on 05/09/2020.
//

#include <cstdlib>
#include "OutFeeds.h"

PlaneFuelSystem::OutFeeds::OutFeeds() {
    this->pumpStates = (int*) malloc(21*sizeof(int));
    this->valveStates = (int*) malloc(40 * sizeof(int));
    this->output = (int**) malloc(2*sizeof(int*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::OutFeeds::~OutFeeds() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

int **PlaneFuelSystem::OutFeeds::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual) {
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

    if (!cases[1] && !cases[5] && !cases[7]) { //all normal, oh yes
        if (f1) this->valveStates[2] = vlvStates;
        if (f4) this->valveStates[8] = vlvStates;
        if (f5) this->valveStates[10] = vlvStates;
        if (f8) this->valveStates[16] = vlvStates;
        this->pumpStates[8] = 1;
        this->pumpStates[17] = 1;
        return this->output;
    }
    if (cases[1] && !cases[5] && !cases[7]) {//case 2- all on aft
        if (f1) this->valveStates[3] = vlvStates;
        if (f8) this->valveStates[17] = vlvStates;
        if (f4) this->valveStates[9] = vlvStates;
        if (f5) this->valveStates[11] = vlvStates;
        if (f1 || f8 || f4 || f5) {
            this->valveStates[1] = 1;
            this->valveStates[19] = 1;
        }
        return this->output;
    }
    if (!cases[1] && cases[5] && !cases[7] && aut) {//case 5 - gravFromOuterTanks (automatic)
        if (f1) this->valveStates[2] = 1;
        if (f8) this->valveStates[16] = 1;
        if (f1 || f8) {
            this->valveStates[0] = 2;
            this->valveStates[18] = 2;
        }

        if (f4) this->valveStates[9] = 1;
        if (f5) this->valveStates[11] = 1;
        if (f4 || f5) {
            this->valveStates[1] = 2;
            this->valveStates[19] = 2;
        }
        return this->output;
    }
    if (cases[7] && aut) {
        //this should not happen
        return nullptr;
    }

    if (cases[5] && !cases[7] && !aut && !someManual) {//case 5 - gravFromOuterTanks (manual)
        if (f4) this->valveStates[8] = 3; //todo is correct?
        if (f4) this->valveStates[9] = 3;
        if (f5) this->valveStates[10] = 3;
        if (f5) this->valveStates[11] = 3;
        if (f4 || f5) {
            this->valveStates[0] = 4;
            this->valveStates[18] = 4;
            this->valveStates[1] = 4;
            this->valveStates[19] = 4;
        }
        return this->output;
    }
    if (cases[5] && !cases[7] && !aut && someManual) {//case 5 - gravFromOuterTanks (manual) (with another-only fwd)
        if (f4) this->valveStates[8] = 3; //todo correct shit with emerg and so
        if (f5) this->valveStates[10] = 3;
        if (f4 || f5) {
            this->valveStates[0] = 4;
            this->valveStates[18] = 4;
        }
        return this->output;
    }

    if (cases[7] && aut) {
        //should never happen
        return nullptr;
    }

    //TODO manual mode
    return nullptr;
}