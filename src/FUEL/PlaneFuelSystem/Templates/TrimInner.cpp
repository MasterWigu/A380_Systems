#include "TrimInner.h"
#include <cstdlib>

PlaneFuelSystem::TrimInner::TrimInner() {
    this->pumpStates = (int*) malloc(21*sizeof(int));
    this->valveStates = (int*) malloc(40 * sizeof(int));
    this->output = (int**) malloc(2*sizeof(int*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::TrimInner::~TrimInner() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

int **PlaneFuelSystem::TrimInner::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = 0;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = 0;

    bool f3 = true; bool f6 = true;
    int vlvStates = aut ? 3 : 1; //if this is called in auto, valves are auto (1) else valves are manual (3)

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[3] > tanks[6] + 50) //if tank3 has more than tank6
        f3 = false;
    if (tanks[6] > tanks[3] + 50) //if tank6 has more than tank3
        f6 = false;

    if (!cases[0] && !cases[3] && !cases[7]) { //all normal, oh yes (aft)
        if (f3) this->valveStates[7] = vlvStates;
        if (f6) this->valveStates[13] = vlvStates;
        this->valveStates[38] = 1; //aft trim bus valve
        this->pumpStates[18] = 1;
        this->pumpStates[19] = 1;
        return this->output;
    }
    if (cases[0] && !cases[7] ) {
        //if case 1 is active, its impossible to have trim->inner transfer
        return this->output;
    }
    if (!cases[0] && cases[3] && !cases[7] ) {//gallery swap for inner (uses fwd)
        if (f3) this->valveStates[6] = vlvStates;
        if (f6) this->valveStates[12] = vlvStates;
        this->valveStates[37] = 1; //fwd trim bus valve
        this->pumpStates[18] = 1;
        this->pumpStates[19] = 1;
        return this->output;
    }
    if (cases[7] && aut) {
        //when we have general failure, no automatic should happen
        return this->output;
    }

    //else, transfer is manual and with general failure (well shit)
    bool gravFeed = true;
    bool possibleFeed = false;
    if (pmpFailures[18] == 0 && vlvFailures[20] != 1 && vlvFailures[21] != 1) { //if valves are failed open, we cant do pumped
        this->pumpStates[18] = 1;
        gravFeed = false;
        possibleFeed = true;
    }
    if (pmpFailures[19] == 0 && vlvFailures[20] != 1 && vlvFailures[21] != 1) {
        this->pumpStates[19] = 1;
        gravFeed = false;
        possibleFeed = true;
    }
    if (gravFeed) {
        if (vlvFailures[20] != 1) { //if valve is not failed closed, we open it
            this->valveStates[20] = 4;
            possibleFeed = true;
        }
        if (vlvFailures[21] != 1) {
            this->valveStates[21] = 4;
            possibleFeed = true;
        }
    }
    if (!possibleFeed) { //if we cant feed, rip
        return nullptr;
    }

    bool possibleDst = false;
    bool aftIntegrity = false;
    bool fwdIntegrity = false;
    bool inLeftAft = false; bool inLeftFwd = false;
    bool inRightAft = false; bool inRightFwd = false;
    if (vlvFailures[38] != 1) { //if aft valve not failed closed, we check aft integrity
        if (vlvFailures[7] != 1) inLeftAft = true;
        if (vlvFailures[13] != 1) inRightAft = true;
        if ((inLeftAft || inRightAft) &&
            vlvFailures[1] != 2 && vlvFailures[19] != 2 &&
            vlvFailures[3] != 2 && vlvFailures[17] != 2 &&
            vlvFailures[5] != 2 && vlvFailures[15] != 2 &&
            vlvFailures[9] != 2 && vlvFailures[11] != 2)

            aftIntegrity = true;
    }
    if (possibleFeed && inLeftAft && inRightAft && aftIntegrity && vlvFailures[37] != 2) { //if we can feed via aft
        this->valveStates[38] = 1;
        this->valveStates[7] = 3;
        this->valveStates[13] = 3;
        return this->output;
    }

    //try for fwd
    if (vlvFailures[37] != 1) { //if aft valve not failed closed, we check fwd integrity
        if (vlvFailures[6] != 1) inLeftFwd = true;
        if (vlvFailures[12] != 1) inRightFwd = true;
        if ((inLeftFwd || inRightFwd) &&
            vlvFailures[0] != 2 && vlvFailures[18] != 2 &&
            vlvFailures[2] != 2 && vlvFailures[16] != 2 &&
            vlvFailures[4] != 2 && vlvFailures[14] != 2 &&
            vlvFailures[8] != 2 && vlvFailures[10] != 2)

            fwdIntegrity = true;
    }
    if (possibleFeed && inLeftFwd && inRightFwd && fwdIntegrity && vlvFailures[38] != 2) { //if we can feed via fwd
        this->valveStates[37] = 1;
        this->valveStates[6] = 3;
        this->valveStates[12] = 3;
        return this->output;
    }

    //see if possible with mix (maintaining balance)
    if (possibleFeed && (inLeftAft || inLeftFwd) && (inRightAft || inRightFwd) && fwdIntegrity && aftIntegrity) {
        if (inLeftAft)
            this->valveStates[7] = 3;
        else
            this->valveStates[6] = 3;
        if (inRightAft)
            this->valveStates[13] = 3;
        else
            this->valveStates[12] = 3;
        this->valveStates[37] = 1;
        this->valveStates[38] = 1;
        return this->output;
    }
    //see if possible with mix (without balance)
    if (possibleFeed && (inLeftAft || inLeftFwd || inRightAft || inRightFwd) && fwdIntegrity && aftIntegrity) {
        if (inLeftAft)
            this->valveStates[7] = 3;
        else if (inLeftFwd)
            this->valveStates[6] = 3;
        if (inRightAft)
            this->valveStates[13] = 3;
        else if (inRightFwd)
            this->valveStates[12] = 3;
        if (this->valveStates[7] || this->valveStates[13])
            this->valveStates[38] = 1;
        if (this->valveStates[6] || this->valveStates[12])
            this->valveStates[37] = 1;

        return this->output;
    }

    return nullptr; //if transfer is impossible
}
