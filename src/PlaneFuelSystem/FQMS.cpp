//
// Created by morei on 01/09/2020.
//
#include <cstdlib>
#include <cmath>
#include "FQMS.h"

namespace PlaneFuelSystem {
    FQMS::FQMS(FuelSystem::FuelSystem* fS, PlaneFuelSystem::FQDC* f) {
        this->fuelSystem = fS;
        this->fqdc = f;
        this->arraysInit();

        this->fwdOccupied = false;
        this->aftOccupied = false;

        this->feedTks = (int *) malloc(4 * sizeof(int));
        this->feedTks[0] = 1; this->feedTks[1] = 4;this->feedTks[2] = 5;this->feedTks[3] = 8;

        this->emergValvesCockpit = false;

        this->inFlight = false;
        this->CGTarget = 0;
    }

    void FQMS::arraysInit() {
        this->mainTransferDest = (bool*) malloc(4*sizeof(bool));
        for (int i = 0; i < 4; i++)
            this->mainTransferDest[i] = false;

        this->mainTransferSrc = (bool*) malloc(4*sizeof(bool));
        for (int i = 0; i < 4; i++)
            this->mainTransferSrc[i] = false;


        //NOTE: case 4 is two cases, for mid or inner, that makes a total of 7 cases instead of 6
        this->abnCases = (bool *) malloc(7 * sizeof(bool));
        for (int i = 0; i < 7; i++)
            this->abnCases[i] = false;

        this->tankLevels = (int *) malloc(15 * sizeof(int));
        for (int i = 0; i < 6; i++)
            this->tankLevels[i] = 0;

        this->commandedPumpStates = (bool* ) malloc(20 * sizeof(bool));
        for (int i = 0; i < 20; i++)
            this->commandedPumpStates[i] = false;

        this->commandedVlvStates = (bool* ) malloc(39 * sizeof(bool));
        for (int i = 0; i < 39; i++)
            this->commandedVlvStates[i] = false;

        this->pumpsFailStates = (int*) malloc(21*sizeof(int));
        for (int i = 0; i < 21; i++)
            this->pumpsFailStates[i] = 0;

        this->vlvsFailStates = (int*) malloc(39*sizeof(int));
        for (int i = 0; i < 39; i++)
            this->vlvsFailStates[i] = 0;

        this->consValvesFailStates = (int*) malloc(7*sizeof(int));
        for (int i = 0; i < 7; i++)
            this->consValvesFailStates[i] = 0;

        this->commandedTransfers = (bool*) malloc(15 * sizeof(bool));
        for (int i = 0; i < 15; i++)
            this->commandedTransfers[i] = false;

        this->lastTransfers = (bool*) malloc(15 * sizeof(bool));
        for (int i = 0; i < 15; i++)
            this->lastTransfers[i] = false;

        this->pumpsCockpitButtons = (bool*) malloc(20 * sizeof(bool));
        for (int i = 0; i < 20; i++)
            this->pumpsCockpitButtons[i] = false;

        this->xfrCockpitButtons = (bool*) malloc(4 * sizeof(bool));
        for (int i = 0; i < 4; i++)
            this->xfrCockpitButtons[i] = false;

        this->crossFeedCockpit = (bool*) malloc(4 * sizeof(bool));
        for (int i = 0; i < 4; i++)
            this->crossFeedCockpit[i] = false;
    }

    void FQMS::detectAbnCases() {
        bool tempCases[8];
        for (int i=0; i<8; i++)
            tempCases[i] = false;

        //CASE 1
        if (this->vlvsFailStates[1] == 1 || this->vlvsFailStates[19] == 1 || //out    tk aft vlvs
            this->vlvsFailStates[5] != 0 || this->vlvsFailStates[15] != 0 || //mid    tk aft vlvs
            this->vlvsFailStates[7] != 0 || this->vlvsFailStates[13] != 0 || //inn    tk aft vlvs
            this->vlvsFailStates[3] != 0 || this->vlvsFailStates[17] != 0 || //feed14 tk aft vlvs
            this->vlvsFailStates[9] != 0 || this->vlvsFailStates[11] != 0 || //feed23 tk aft vlvs
            this->vlvsFailStates[38] == 2 || //trim to aft vlv
            this->vlvsFailStates[37] == 1 || //trim to fwd vlv
            this->consValvesFailStates[5] == 1 || this->consValvesFailStates[6] == 1) { //jettison valves


            tempCases[0] = true;
        }


        //CASE 2
        if (this->vlvsFailStates[0] == 1 || this->vlvsFailStates[18] == 1 || //out    tk fwd vlvs
            this->vlvsFailStates[4] == 1 || this->vlvsFailStates[14] == 1 || //mid    tk fwd vlvs
            this->vlvsFailStates[6] == 1 || this->vlvsFailStates[12] == 1 || //inn    tk fwd vlvs
            this->vlvsFailStates[2] != 0 || this->vlvsFailStates[16] != 0 || //feed14 tk fwd vlvs
            this->vlvsFailStates[8] != 0 || this->vlvsFailStates[10] != 0) { //feed23 tk fwd vlvs

            tempCases[1] = true;
        }

        //CASE 3
        if (this->vlvsFailStates[0] == 2 || this->vlvsFailStates[18] == 2) { //out tk fwd vlvs
            tempCases[2] = true;
        }

        //CASE 4 INNER
        if (this->pumpsFailStates[11] == 1 || this->pumpsFailStates[13] == 1) { //inn fwd pumps
            tempCases[3] = true;
        }

        //CASE 4 MID
        if (this->pumpsFailStates[9] == 1 || this->pumpsFailStates[15] == 1) { //mid fwd pumps
            tempCases[4] = true;
        }

        //CASE 5
        if (this->pumpsFailStates[8] == 1 || this->pumpsFailStates[17] == 1) { //out fwd pumps
            tempCases[5] = true;
        }

        //CASE 6
        if (this->vlvsFailStates[37] == 2) { //trim to fwd vlv
            tempCases[6] = true;
        }

        //check conflicting cases (if we have any, declare general fault (pseudo case 7)
        if (tempCases[0] && tempCases[1] || //all on fwd && all on aft
            tempCases[0] && tempCases[2] || //all on fwd && to out on aft
            tempCases[0] && tempCases[3] || //all on fwd && swap for inn
            tempCases[0] && tempCases[4] || //all on fwd && swap for mid
            tempCases[0] && tempCases[5] || //all on fwd && grav trans from out (needs both galleries)
            tempCases[1] && tempCases[5] ) {//all on aft && grav trans from out (needs both galleries)

            tempCases[7] = true;
        }

    }

    //failPumpArray: {0 = Normal; 1 = Failed (off); 2 = Failed (On)} !!!Failed on is not used and may crash all of this, idk, i forgot to add it
    //failVlvArray: {0 = normal; 1 = Failed open; 2 = Failed closed

    //cases: 0 - Case 1
    //       1 - Case 2
    //       2 - Case 3
    //       3 - Case 4 (inner)
    //       4 - Case 4 (mid)
    //       5 - Case 5
    //       6 - Case 6
    //       7 - Multiple failures (ignores other cases, this is sparta now)


    //Possible transfers: 0  - Inner    -> Feed14
    //                    1  - Inner    -> Feed23
    //                    2  - Inner    -> Feeds
    //                    3  - Inner    -> Outer
    //                    4  - Mid      -> Feed14
    //                    5  - Mid      -> Feed23
    //                    6  - Mid      -> Feeds
    //                    7  - Mid      -> Outer
    //                    8  - Trim     -> Inner
    //                    9  - Trim     -> Mid
    //                    10 - Trim     -> Feeds
    //                    11 - Outer    -> Inner
    //                    12 - Outer    -> Mid
    //                    13 - Outer    -> Feeds
    //                    14 - ALL      -> Jettison

    void FQMS::updateLoop(int remMinutes, int GW, double currCG) {
        this->updateCGTarget(GW);
        this->pumpStatusCheck();
        this->vlvStatusCheck();
        this->getTankLevels();
        this->detectAbnCases();
        this->selectTransfers(remMinutes, currCG);

        this->applyState();
    }

    void FQMS::updateCGTarget(int GW) {
        double GWt = GW / 1000.0;
        this->CGTarget = (5058.4908643318586 + sqrt(25588329.824528873888 - 253.782771599910176 * (101088.31599889736 - GW))) / 126.891385799955088;
    }

    void FQMS::selectTransfers(int remFltTime, double currCG) {
        if (this->abnCases[7])
            return; //if we are have too many failures, no automatic transfers are possible
        if (this->abnCases[0]) {
            //this->selectCase1Transfers();
            return;
        }
        if (this->abnCases[1]) {
            //this->selectCase2Transfers();
            return;
        }
        if (this->abnCases[6]) {
            //this->selectCase6Transfers();
        }
        this->selectNormalTransfers(remFltTime, currCG);

    }

    void FQMS::selectNormalTransfers(int remTimeMins, double currCG) {
        bool mainFoundTank = false;
        this->fwdOccupied = false;
        this->aftOccupied = false;

        for (int i=0; i<15; i++) {
            this->lastTransfers[i] = this->commandedTransfers[i];
            this->commandedTransfers[i] = false;
        }
        if (!inFlight)
            return;

        //MAIN TRANSFERS
        if (this->tankLevels[3]+this->tankLevels[6] > 200 || this->tankLevels[2]+ this->tankLevels[7] > 8000 ) { //different thresholds
            int innOrMid = this->tankLevels[3]+this->tankLevels[6] > 200 ? 0 : 4; //if inner with fuel, select 0/1, if empty, selects 4/5
            mainFoundTank = true;

            if (remTimeMins < 90) {
                if (this->tankLevels[1] < 16560 || this->tankLevels[8] < 16560 ||
                        (this->lastTransfers[innOrMid] && (this->tankLevels[1] < 17560 || this->tankLevels[8] < 17560 ))) {
                    this->commandedTransfers[innOrMid] = true;
                    this->fwdOccupied = true;
                }
                if (this->tankLevels[4] < 17840 || this->tankLevels[5] < 17840 ||
                    (this->lastTransfers[innOrMid+1] && (this->tankLevels[4] < 18840 || this->tankLevels[5] < 18840 ))) {
                    this->commandedTransfers[innOrMid + 1] = true;
                    this->fwdOccupied = true;
                }
            }
            else { //Remaining time > 90min
                if (this->tankLevels[1] < 19560 || this->tankLevels[8] < 19560 ||
                    (this->lastTransfers[innOrMid] && (this->tankLevels[1] < 20560 || this->tankLevels[8] < 20560 ))) {
                    this->commandedTransfers[innOrMid] = true;
                    this->fwdOccupied = true;
                }
                if (this->tankLevels[4] < 17840 || this->tankLevels[5] < 17840 ||
                    (this->lastTransfers[innOrMid+1] && (this->tankLevels[4] < 18840 || this->tankLevels[5] < 18840))) {
                    this->commandedTransfers[innOrMid + 1] = true;
                    this->fwdOccupied = true;
                }
            }
        }
        if (!mainFoundTank && this->tankLevels[2]+ this->tankLevels[7] > 200) {
            mainFoundTank = true;
            if ((this->tankLevels[1] < 19560 || this->tankLevels[8] < 19560 || this->tankLevels[4] < 19560 || this->tankLevels[5] < 19560) &&
                (!this->lastTransfers[6] && this->tankLevels[1] < 20560 && this->tankLevels[8] < 20560 && this->tankLevels[4] < 20560 && this->tankLevels[5] < 20560) ||  // to start
                (this->lastTransfers[6] && (this->tankLevels[1] < 20560 || this->tankLevels[8] < 20560 ||  this->tankLevels[4] < 20560 || this->tankLevels[5] < 20560))) { //to continue
                this->commandedTransfers[6] = true;
                this->fwdOccupied = true;
            }
        }
        if (!mainFoundTank && this->tankLevels[10] > 100) {
            mainFoundTank = true;
            if ((this->tankLevels[1] < 6000 || this->tankLevels[8] < 6000 || this->tankLevels[4] < 6000 || this->tankLevels[5] < 6000) || // to start
                this->lastTransfers[10]) { //to continue
                this->commandedTransfers[10] = true;
                this->aftOccupied = true;
            }
        }

        if (!mainFoundTank && this->tankLevels[0] + this->tankLevels[9] > 200) { //technically simplified (the tanks should be treated as pairs instead of all them but that would add complexity
            if ((this->tankLevels[1] < 4000 || this->tankLevels[8] < 4000 || this->tankLevels[4] < 4000 || this->tankLevels[5] < 4000) || // to start
                (this->lastTransfers[13] && (this->tankLevels[1] < 4500 || this->tankLevels[8] < 4500 || this->tankLevels[4] < 4500 || this->tankLevels[5] < 4500))) { //to continue
                this->commandedTransfers[13] = true;
                this->fwdOccupied = true;
            }
        }

        //LOAD TRANSFERS

        //To outer tanks
        if (this->FOB > 50000 && this->tankLevels[0]+ this->tankLevels[9] < 16230) { //if fob>50t && outer not full
            if (!fwdOccupied) {
                if (this->tankLevels[3]+this->tankLevels[6] > 200) { //if inner not empty
                    this->commandedTransfers[3] = true;
                    fwdOccupied = true;
                }
                else if (this->tankLevels[2]+ this->tankLevels[7] > 200) {
                    this->commandedTransfers[7] = true;
                    fwdOccupied = true;
                }
            }
        }

        //From trim Tank
        if (!aftOccupied && true) { //TODO add time and FL conditions
            if (this->tankLevels[1]+this->tankLevels[4]+this->tankLevels[5]+this->tankLevels[8] < 89400) { //if feeds not full
                this->commandedTransfers[10] = true;
                aftOccupied = true;
            }
            else if (this->tankLevels[2]+this->tankLevels[7] < 57200) { //if mids not empty
                this->commandedTransfers[9] = true;
                aftOccupied = true;
            }
            else if (this->tankLevels[3]+ this->tankLevels[6] < 72400) { //if inners not empty
                this->commandedTransfers[8] = true;
                aftOccupied = true;
            }
        }

        //From outer tanks
        if (!fwdOccupied && (this->tankLevels[0] > 4000 || this->tankLevels[9] > 4000) && true) { //TODO add time and FL conditions
            if (this->tankLevels[1]+this->tankLevels[4]+this->tankLevels[5]+this->tankLevels[8] < 89400) { //if feeds not full
                this->commandedTransfers[13] = true;
                fwdOccupied = true;
            }
            else if (this->tankLevels[2]+this->tankLevels[7] < 57200) { //if mids not full
                this->commandedTransfers[12] = true;
                fwdOccupied = true;
            }
            else if (this->tankLevels[3]+ this->tankLevels[6] < 72400) { //if inners not full
                this->commandedTransfers[11] = true;
                fwdOccupied = true;
            }
        }

        //CG TRANSFERS from trim
        if (!aftOccupied && currCG > this->CGTarget || ((this->lastTransfers[8] || this->lastTransfers[9] || this->lastTransfers[10]) && currCG > CGTarget - 1)) {
            if (this->tankLevels[3]+ this->tankLevels[6] > 250) { //if inners not empty
                if (this->tankLevels[3]+ this->tankLevels[6] < 72400) {
                    this->commandedTransfers[8] = true;
                    aftOccupied = true;
                }
            }
            else if (this->tankLevels[2]+this->tankLevels[7] > 250) { //if mids not empty
                if (this->tankLevels[2]+this->tankLevels[7] < 57200) {
                    this->commandedTransfers[9] = true;
                    aftOccupied = true;
                }
            }
            else if (this->tankLevels[1]+this->tankLevels[4]+this->tankLevels[5]+this->tankLevels[8] < 89400) { //if feeds not full
                this->commandedTransfers[10] = true;
                aftOccupied = true;
            }
        }

        //COLD AUTOMATIC TRANSFER
        //TODO when temp is simulated
    }

    void FQMS::getTankLevels() {
        int fqdcRead[] = {this->fqdc->readQuantitySensorAGP(0),
                         this->fqdc->readQuantitySensorAGP(1),
                         this->fqdc->readQuantitySensorAGP(2),
                         this->fqdc->readQuantitySensorAGP(3),
                         this->fqdc->readQuantitySensorAGP(4),
                         this->fqdc->readQuantitySensorAGP(5),
                         this->fqdc->readQuantitySensorAGP(6),
                         this->fqdc->readQuantitySensorAGP(7),
                         this->fqdc->readQuantitySensorAGP(8),
                         this->fqdc->readQuantitySensorAGP(9),
                         this->fqdc->readQuantitySensorAGP(10),
                         this->fqdc->readQuantitySensorAGP(11),
                         this->fqdc->readQuantitySensorAGP(12),
                         this->fqdc->readQuantitySensorAGP(13),
                         this->fqdc->readQuantitySensorAGP(14)};

        int directRead[] = {this->fqdc->readQuantitySensorDirect(0),
                           this->fqdc->readQuantitySensorDirect(1),
                           this->fqdc->readQuantitySensorDirect(2),
                           this->fqdc->readQuantitySensorDirect(3),
                           this->fqdc->readQuantitySensorDirect(4),
                           this->fqdc->readQuantitySensorDirect(5),
                           this->fqdc->readQuantitySensorDirect(6),
                           this->fqdc->readQuantitySensorDirect(7),
                           this->fqdc->readQuantitySensorDirect(8),
                           this->fqdc->readQuantitySensorDirect(9),
                           this->fqdc->readQuantitySensorDirect(10),
                           this->fqdc->readQuantitySensorDirect(11),
                           this->fqdc->readQuantitySensorDirect(12),
                           this->fqdc->readQuantitySensorDirect(13),
                           this->fqdc->readQuantitySensorDirect(14)};

        this->FOB = 0;
        for (int i = 0; i< 15; i++) {
            double diff = (1.0 * directRead[i]) / (1.0 * fqdcRead[i]);
            if (diff < 0.98 || diff > 1.02) {
                //exception maybe, is failure
            }
            this->tankLevels[i] = fqdcRead[i];
            this->FOB += fqdcRead[i];
        }
    }

    void FQMS::pumpStatusCheck() {
        for (int i=0; i<21; i++) {
            if (this->commandedPumpStates[i] && this->fuelSystem->readPumpState(i) != 1 ||
                !this->commandedPumpStates[i] && this->fuelSystem->readPumpState(i) != 0) {
                this->pumpsFailStates[i] = 1; //failed
            }
            else {
                this->pumpsFailStates[i] = 0;
            }
        }
    }

    void FQMS::vlvStatusCheck() {
        for (int i = 0; i<39; i++) {
            if (i>21 && i<28) {
                this->vlvsFailStates[i] = 0; //these dont exist
                continue;
            }
            if (this->commandedVlvStates[i] && this->fuelSystem->readValveState(i) != 1) {
                this->vlvsFailStates[i] = 1; //failed close
            }
            else if (!this->commandedVlvStates[i] && this->fuelSystem->readValveState(i) != 0) {
                this->vlvsFailStates[i] = 2; //failed open
            }
            else {
                this->vlvsFailStates[i] = 0; //normal
            }
        }
    }

    void FQMS::applyState() {
        this->applyPumpState();
        this->applyValveState();
    }

    void FQMS::applyPumpState() {
        //pumps
        for (int i = 0; i< 20; i++) {
            this->fuelSystem->setPumpState(i, this->commandedPumpStates[i]);
            if (this->fuelSystem->readPumpState(i) != this->commandedPumpStates[i]) {
                this->pumpsFailStates[i] = 1;
            }
        }
        //turn off symetric pump to the one failed if we are trying to power on the failed (only for main wing pumps)
        if (this->pumpsFailStates[8] && this->commandedPumpStates[8]) { //outer
            this->fuelSystem->setPumpState(8, 0);
            this->fuelSystem->setPumpState(17, 0);
        }
        if (this->pumpsFailStates[17] && this->commandedPumpStates[17]) { //outer
            this->fuelSystem->setPumpState(8, 0);
            this->fuelSystem->setPumpState(17, 0);
        }
        if (this->pumpsFailStates[9] && this->commandedPumpStates[9]) { //mid fwd
            this->fuelSystem->setPumpState(9, 0);
            this->fuelSystem->setPumpState(15, 0);
        }
        if (this->pumpsFailStates[15] && this->commandedPumpStates[15]) { //mid fwd
            this->fuelSystem->setPumpState(15, 0);
            this->fuelSystem->setPumpState(9, 0);
        }
        if (this->pumpsFailStates[10] && this->commandedPumpStates[10]) { //mid aft
            this->fuelSystem->setPumpState(10, 0);
            this->fuelSystem->setPumpState(16, 0);
        }
        if (this->pumpsFailStates[16] && this->commandedPumpStates[16]) { //mid aft
            this->fuelSystem->setPumpState(16, 0);
            this->fuelSystem->setPumpState(10, 0);
        }
        if (this->pumpsFailStates[11] && this->commandedPumpStates[11]) { //inner fwd
            this->fuelSystem->setPumpState(11, 0);
            this->fuelSystem->setPumpState(13, 0);
        }
        if (this->pumpsFailStates[13] && this->commandedPumpStates[13]) { //inner fwd
            this->fuelSystem->setPumpState(13, 0);
            this->fuelSystem->setPumpState(11, 0);
        }
        if (this->pumpsFailStates[12] && this->commandedPumpStates[12]) { //inner aft
            this->fuelSystem->setPumpState(12, 0);
            this->fuelSystem->setPumpState(14, 0);
        }
        if (this->pumpsFailStates[14] && this->commandedPumpStates[14]) { //inner aft
            this->fuelSystem->setPumpState(14, 0);
            this->fuelSystem->setPumpState(12, 0);
        }

    }

    void FQMS::applyValveState() {
        for (int i = 0; i< 39; i++) {
            if (i > 21 && i < 28) continue;

            this->fuelSystem->setValveState(i, this->commandedVlvStates[i]);
            if (this->fuelSystem->readValveState(i) != this->commandedVlvStates[i]) { //if valve is failed
                if (this->fuelSystem->readValveState(i) == 1) //if valve is open
                    this->vlvsFailStates[i] = 1; //failed open
                else                                        //else if valve is closed
                    this->vlvsFailStates[i] = 2; //failed closed
            }
        }
        //when a valve fails open, we can't do nothing
        //if it fails closed, we close the opposite

        if (this->vlvsFailStates[0] == 2 && this->commandedVlvStates[0]) { //outer fwd closed
            this->fuelSystem->setValveState(0, 0);
            this->fuelSystem->setValveState(18, 0);
        }
        if (this->vlvsFailStates[18] == 2 && this->commandedVlvStates[18]) { //outer fwd closed
            this->fuelSystem->setValveState(0, 0);
            this->fuelSystem->setValveState(18, 0);
        }
        if (this->vlvsFailStates[1] == 2 && this->commandedVlvStates[1]) { //outer aft closed
            this->fuelSystem->setValveState(1, 0);
            this->fuelSystem->setValveState(19, 0);
        }
        if (this->vlvsFailStates[19] == 2 && this->commandedVlvStates[19]) { //outer aft closed
            this->fuelSystem->setValveState(1, 0);
            this->fuelSystem->setValveState(19, 0);
        }
        if (this->vlvsFailStates[2] == 2 && this->commandedVlvStates[2]) { //feed14 fwd closed
            this->fuelSystem->setValveState(2, 0);
            this->fuelSystem->setValveState(16, 0);
        }
        if (this->vlvsFailStates[16] == 2 && this->commandedVlvStates[16]) { //feed14 fwd closed
            this->fuelSystem->setValveState(16, 0);
            this->fuelSystem->setValveState(2, 0);
        }
        if (this->vlvsFailStates[3] == 2 && this->commandedVlvStates[3]) { //feed14 aft closed
            this->fuelSystem->setValveState(3, 0);
            this->fuelSystem->setValveState(17, 0);
        }
        if (this->vlvsFailStates[17] == 2 && this->commandedVlvStates[17]) { //feed14 aft closed
            this->fuelSystem->setValveState(17, 0);
            this->fuelSystem->setValveState(3, 0);
        }
        if (this->vlvsFailStates[4] == 2 && this->commandedVlvStates[4]) { //mid fwd closed
            this->fuelSystem->setValveState(4, 0);
            this->fuelSystem->setValveState(14, 0);
        }
        if (this->vlvsFailStates[14] == 2 && this->commandedVlvStates[14]) { //mid fwd closed
            this->fuelSystem->setValveState(14, 0);
            this->fuelSystem->setValveState(4, 0);
        }
        if (this->vlvsFailStates[5] == 2 && this->commandedVlvStates[5]) { //mid aft closed
            this->fuelSystem->setValveState(5, 0);
            this->fuelSystem->setValveState(15, 0);
        }
        if (this->vlvsFailStates[15] == 2 && this->commandedVlvStates[15]) { //mid aft closed
            this->fuelSystem->setValveState(15, 0);
            this->fuelSystem->setValveState(5, 0);
        }
        if (this->vlvsFailStates[6] == 2 && this->commandedVlvStates[6]) { //inner fwd closed
            this->fuelSystem->setValveState(6, 0);
            this->fuelSystem->setValveState(12, 0);
        }
        if (this->vlvsFailStates[12] == 2 && this->commandedVlvStates[12]) { //inner fwd closed
            this->fuelSystem->setValveState(12, 0);
            this->fuelSystem->setValveState(6, 0);
        }
        if (this->vlvsFailStates[7] == 2 && this->commandedVlvStates[7]) { //inner aft closed
            this->fuelSystem->setValveState(7, 0);
            this->fuelSystem->setValveState(13, 0);
        }
        if (this->vlvsFailStates[13] == 2 && this->commandedVlvStates[13]) { //inner aft closed
            this->fuelSystem->setValveState(13, 0);
            this->fuelSystem->setValveState(7, 0);
        }
        if (this->vlvsFailStates[8] == 2 && this->commandedVlvStates[8]) { //feed23 fwd closed
            this->fuelSystem->setValveState(8, 0);
            this->fuelSystem->setValveState(10, 0);
        }
        if (this->vlvsFailStates[10] == 2 && this->commandedVlvStates[10]) { //feed23 fwd closed
            this->fuelSystem->setValveState(10, 0);
            this->fuelSystem->setValveState(8, 0);
        }
        if (this->vlvsFailStates[9] == 2 && this->commandedVlvStates[9]) { //feed23 aft closed
            this->fuelSystem->setValveState(9, 0);
            this->fuelSystem->setValveState(11, 0);
        }
        if (this->vlvsFailStates[11] == 2 && this->commandedVlvStates[11]) { //feed23 aft closed
            this->fuelSystem->setValveState(11, 0);
            this->fuelSystem->setValveState(9, 0);
        }
    }

    int FQMS::getPumpStateECAM(int id) {
        if (this->pumpsFailStates[id] == 0 && this->pumpsCockpitButtons[id]) {
            if(this->commandedPumpStates)
                return 1; //pump running
            return 0; //pump off
        }
        return 3;
        //4 (abnOn) and 5 (LO)  are not implemented
    }

}