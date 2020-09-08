//
// Created by morei on 08/09/2020.
//

#include "TrimInner.h"
#include <cstdlib>

PlaneFuelSystem::TrimInner::TrimInner() {
    this->pumpStates = (bool*) malloc(21*sizeof(bool));
    this->valveStates = (bool*) malloc(40 * sizeof(bool));
    this->output = (bool**) malloc(2*sizeof(bool*));
    this->output[0] = this->pumpStates;
    this->output[1] = this->valveStates;
}

PlaneFuelSystem::TrimInner::~TrimInner() {
    free(this->valveStates);
    free(this->pumpStates);
    free(this->output);
}

bool **PlaneFuelSystem::TrimInner::getTemplate(const int* tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut) {
    for (int i = 0; i < 40; i++) this->valveStates[i] = false;
    for (int i = 0; i< 21; i++) this->pumpStates[i] = false;

    bool f3 = true; bool f6 = true;

    //get if some tank has less, if yes, we only feed that (until they equalize)
    if (tanks[3] > tanks[6] + 50) //if tank3 has more than tank6
        f3 = false;
    if (tanks[6] > tanks[3] + 50) //if tank6 has more than tank3
        f6 = false;

    if (!cases[0] && !cases[3] && !cases[7]) { //all normal, oh yes (aft)
        if (f3) this->valveStates[7] = true;
        if (f6) this->valveStates[13] = true;
        this->valveStates[38] = true; //aft trim bus valve
        this->pumpStates[18] = true;
        this->pumpStates[19] = true;
        return this->output;
    }
    if (cases[0] && !cases[7] ) {
        //if case 1 is active, its impossible to have trim->inner transfer
        return this->output;
    }
    if (!cases[0] && cases[3] && !cases[7] ) {//gallery swap for inner (uses fwd)
        if (f3) this->valveStates[6] = true;
        if (f6) this->valveStates[12] = true;
        this->valveStates[37] = true; //fwd trim bus valve
        this->pumpStates[18] = true;
        this->pumpStates[19] = true;
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
        this->pumpStates[18] = true;
        gravFeed = false;
        possibleFeed = true;
    }
    if (pmpFailures[19] == 0 && vlvFailures[20] != 1 && vlvFailures[21] != 1) {
        this->pumpStates[19] = true;
        gravFeed = false;
        possibleFeed = true;
    }
    if (gravFeed) {
        if (vlvFailures[20] != 1) { //if valve is not failed closed, we open it
            this->valveStates[20] = true;
            possibleFeed = true;
        }
        if (vlvFailures[21] != 1) {
            this->valveStates[21] = true;
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
        this->valveStates[38] = true;
        this->valveStates[7] = true;
        this->valveStates[13] = true;
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
        this->valveStates[37] = true;
        this->valveStates[6] = true;
        this->valveStates[12] = true;
        return this->output;
    }

    //see if possible with mix (maintaining balance)
    if (possibleFeed && (inLeftAft || inLeftFwd) && (inRightAft || inRightFwd) && fwdIntegrity && aftIntegrity) {
        if (inLeftAft)
            this->valveStates[7] = true;
        else
            this->valveStates[6] = true;
        if (inRightAft)
            this->valveStates[13] = true;
        else
            this->valveStates[12] = true;
        this->valveStates[37] = true;
        this->valveStates[38] = true;
        return this->output;
    }
    //see if possible with mix (without balance)
    if (possibleFeed && (inLeftAft || inLeftFwd || inRightAft || inRightFwd) && fwdIntegrity && aftIntegrity) {
        if (inLeftAft)
            this->valveStates[7] = true;
        else if (inLeftFwd)
            this->valveStates[6] = true;
        if (inRightAft)
            this->valveStates[13] = true;
        else if (inRightFwd)
            this->valveStates[12] = true;
        if (this->valveStates[7] || this->valveStates[13])
            this->valveStates[38] = true;
        if (this->valveStates[6] || this->valveStates[12])
            this->valveStates[37] = true;

        return this->output;
    }

    return nullptr; //if transfer is impossible
}
