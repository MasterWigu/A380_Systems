//
// Created by morei on 05/09/2020.
//

#include <cstdlib>
#include "OutFeeds.h"

PlaneFuelSystem::OutFeeds::OutFeeds() {
    this->pumpStates = (bool*) malloc(21*sizeof(bool));
    this->valveStates = (bool*) malloc(40 * sizeof(bool));
    this->output = (bool**) malloc(2*sizeof(bool*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::OutFeeds::~OutFeeds() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

bool **PlaneFuelSystem::OutFeeds::getTemplate(const int* tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut, bool someManual) {
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

    if (!cases[1] && !cases[5] && !cases[7]) { //all normal, oh yes
        if (f1) this->valveStates[2] = true;
        if (f4) this->valveStates[8] = true;
        if (f5) this->valveStates[10] = true;
        if (f8) this->valveStates[16] = true;
        this->pumpStates[8] = true;
        this->pumpStates[17] = true;
        return this->output;
    }
    if ((cases[1] || cases[5]) && !cases[7] && aut) {//case 5 - gravFromOuterTanks (automatic) or case 2- all on aft
        if (f1) this->valveStates[2] = true;
        if (f8) this->valveStates[16] = true;
        if (f1 || f8) {
            this->valveStates[0] = true;
            this->valveStates[18] = true;
        }

        if (f4) this->valveStates[9] = true;
        if (f5) this->valveStates[11] = true;
        if (f4 || f5) {
            this->valveStates[1] = true;
            this->valveStates[19] = true;
        }
        return this->output;
    }
    if (cases[7] && aut) {
        //TODO failure
        return this->output;
    }

    if (cases[5] && !cases[7] && !aut && !someManual) {//case 5 - gravFromOuterTanks (manual)
        if (f4) this->valveStates[8] = true;
        if (f4) this->valveStates[9] = true;
        if (f5) this->valveStates[10] = true;
        if (f5) this->valveStates[11] = true;
        if (f4 || f5) {
            this->valveStates[0] = true;
            this->valveStates[18] = true;
            this->valveStates[1] = true;
            this->valveStates[19] = true;
        }
        return this->output;
    }
    if (cases[5] && !cases[7] && !aut && someManual) {//case 5 - gravFromOuterTanks (manual) (with another-only fwd)
        if (f4) this->valveStates[8] = true; //todo correct shit with emerg and so
        if (f5) this->valveStates[10] = true;
        if (f4 || f5) {
            this->valveStates[0] = true;
            this->valveStates[18] = true;
        }
        return this->output;
    }

    if (cases[7] && aut) {
        //TODO failure
        return this->output;
    }

    //TODO manual mode


    return this->output;
}