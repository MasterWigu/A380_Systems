//
// Created by morei on 01/09/2020.
//
#include <cstdlib>
#include "FQMS.h"

namespace PlaneFuelSystem {
    FQMS::FQMS(FuelSystem::FuelSystem* fS, PlaneFuelSystem::FQDC* f) {
        this->fuelSystem = fS;
        this->fqdc = f;
        this->arraysInit();

        this->fwdTransferInProgress = -1;
        this->aftTransferInProgress = -1;

        this->threshold14 = 19560;
        this->threshold23 = 20840;
        this->feedTks = (int *) malloc(4 * sizeof(int));
        this->feedTks[0] = 1; this->feedTks[1] = 4;this->feedTks[2] = 5;this->feedTks[3] = 8;

        this->emergValvesCockpit = false;
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

        this->commandedVlvStates = (bool* ) malloc(40 * sizeof(bool));
        for (int i = 0; i < 40; i++)
            this->commandedVlvStates[i] = false;

        this->pumpsFailStates = (int*) malloc(21*sizeof(int));
        for (int i = 0; i < 21; i++)
            this->pumpsFailStates[i] = 0;

        this->vlvsFailStates = (int*) malloc(40*sizeof(int));
        for (int i = 0; i < 40; i++)
            this->vlvsFailStates[i] = 0;

        this->consValvesFailStates = (int*) malloc(7*sizeof(int));
        for (int i = 0; i < 7; i++)
            this->consValvesFailStates[i] = 0;

        this->commandedAutoTransfers = (bool*) malloc(sizeof(bool));



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

    //failPumpArray: {0 = Normal; 1 = Failed (off)}
    //failVlvArray: {0 = normal; 1 = Failed open; 2 = Failed closed

    //cases: 0 - Case 1
    //       1 - Case 2
    //       2 - Case 3
    //       3 - Case 4 (inner)
    //       4 - Case 4 (mid)
    //       5 - Case 5
    //       6 - Case 6
    //       7 - Multiple failures (ignores other cases, this is sparta now)

    //commandedTransfers: 0  - Inner  -> Feed14
    //                    1  - Inner  -> Feed23
    //                    2  - Mid+8t -> Feed14
    //                    3  - Mid+8t -> Feed23
    //                    4  - Mid-8t -> Feeds
    //                    5  - Trim   -> Feeds
    //                    6  - Outer  -> Feeds
    //                    7  - Inner  -> Outer
    //                    8  - Mid    -> Outer
    //                    9  - Trim   -> Inner
    //                    10 - Trim   -> Mid
    //                    (5 - Trim   -> Feeds)
    //                    11 - Outer  -> Inner
    //                    12 - Outer  -> Mid
    //                    (6 - Outer  -> Feeds)



    //Possible transfers: 1 - Main           - Inner  -> Feed  (fwd)
    //                    2 - Main           - Mid    -> Feed  (fwd)

    //                    3- Main/Load/CG   - Trim   -> Feed  (aft)
    //                    4- Load/CG        - Trim   -> Mid   (aft)
    //                    5- Load/CG        - Trim   -> Inner (aft)
    //                    6- Main/Load/Cold - Outer  -> Feed  (fwd)
    //                    7- Load/Cold      - Outer  -> Mid   (fwd)
    //                    8- Load/Cold      - Outer  -> Inner (fwd)
    //                    9 - Load           - Inner  -> Outer (fwd)
    //                    10 - Load           - Mid    -> Outer (fwd)
    //                    11- Inb.           - Inner  -> Inner (fwd)
    //                    12- Inb.           - Mid    -> Mid   (fwd)
    //                    13- Inb.           - Outer  -> Outer (fwd)




    //                    15- Manual         - Outer  -> Feeds  (fwd)
    //                    15- Manual (grav)  - Outer  -> Feeds (fwd + aft) or (fwd)
    //                    15- Manual         - Trim   -> Inner  (aft)
    //                    15- Manual (grav)  - Trim   -> Inner  (aft)
    //                    15- Manual         - Inner  -> Feeds  (aft)
    //                    15- Manual         - Mid    -> Feeds  (aft)

    //                    15- Manual (Jett.) - All    -> Jetti. (fwd + aft) - stops all
    //                    15- Manual         - Feed23 -> Feed23 (none)
    //                    15- Manual         - Feed23 -> Feed23 (none)

    //                    14- Inb.           - Feed14 -> Feed14 (none) (manual)
    //                    15- Inb.           - Feed23 -> Feed23 (none) (manual)


    void FQMS::updateLoop(int remMinutes) {
        this->pumpStatusCheck();
        this->vlvStatusCheck();
        this->getTankLevels();
        this->detectAbnCases();
        this->checkMainTransfers(remMinutes);

        this->applyState();
    }

    void FQMS::



    void FQMS::checkMainTStart() {
        bool needsTransfer = false;
        if (fwdTransferInProgress != 1 && aftTransferInProgress != 1) {//if we are not making any main transfer
            if (this->tankLevels[1] < this->threshold14) {
                this->mainTransferDest[0] = true;
                needsTransfer = true;
            }
            if (this->tankLevels[4] < this->threshold23) {
                this->mainTransferDest[1] = true;
                needsTransfer = true;
            }
            if (this->tankLevels[5] < this->threshold23) {
                this->mainTransferDest[2] = true;
                needsTransfer = true;
            }
            if (this->tankLevels[8] < this->threshold14) {
                this->mainTransferDest[3] = true;
                needsTransfer = true;
            }
        }
        else if (fwdTransferInProgress == 1 || aftTransferInProgress == 1) { //if we are already making main transfer
            needsTransfer = true;
            bool equalThresholds = this->threshold14 == this->threshold23; //to see if we have to balance the 4 feeds, or by the pair
            if (equalThresholds) {
                int lower = 400000;
                for (int i = 0; i<4;i++)
                    if (this->mainTransferDest[i] && this->tankLevels[this->feedTks[i]] < lower)
                        lower = this->tankLevels[this->feedTks[i]];

                for (int i = 0; i<4;i++)
                    if (this->tankLevels[this->feedTks[i]] < lower)
                        this->mainTransferDest[i] = true;
            }
            else {
                int lower;
                int indexes[4] = {0, 3, 1, 2};
                for (int j = 0; j<2; j++) {
                    lower = 400000;
                    for (int i = 0; i < 2; i++)
                        if (this->mainTransferDest[indexes[2*j + i]] && this->tankLevels[this->feedTks[indexes[2*j + i]]] < lower)
                            lower = this->tankLevels[this->feedTks[indexes[2*j + i]]];

                    for (int i = 0; i < 2; i++)
                        if (this->tankLevels[this->feedTks[indexes[2*j + i]]] < lower)
                            this->mainTransferDest[indexes[2*j + i]] = true;
                }
            }

        }

        if (needsTransfer) { //if transfer is needed, we need to check which tank
            this->mainTransferSrc[0] = false; this->mainTransferSrc[1] = false; this->mainTransferSrc[2] = false; this->mainTransferSrc[3] = false;
            if (this->fwdTransferInProgress == 1) this->fwdTransferInProgress = 0;
            if (this->aftTransferInProgress == 1) this->aftTransferInProgress = 0;

            if (this->tankLevels[3] + this->tankLevels[6] > 200) {
                this->mainTransferSrc[0] = true;
                this->fwdTransferInProgress = 1;
            }
            else if (this->tankLevels[2] + this->tankLevels[7] > 200) {
                this->mainTransferSrc[2] = true;
                this->fwdTransferInProgress = 1;
            }
            else if (this->tankLevels[10] > 200) {
                this->mainTransferSrc[3] = true;
                this->aftTransferInProgress = 1;
            }
            else if (this->tankLevels[0] + this->tankLevels[9] > 200) {
                this->mainTransferSrc[4] = true;
                this->fwdTransferInProgress = 1;
            }
        }
    }

    void FQMS::checkMainTStop() {
        // we dont have to stop because of src empty, the start function will change the src automatically, or terminate if no src is avail

        if (fwdTransferInProgress != 1 && aftTransferInProgress != 1) {//if we are not making any main transfer
            return;
        }

        bool stop = false;
        if (this->threshold14 == this->threshold23) {
            if (fwdTransferInProgress == 1) { //if is NOT trim transfer
                for (int i = 0; i < 4; i++) {
                    if (this->tankLevels[this->feedTks[i]] > threshold14 + 1000)
                        stop = true;
                }
                if (stop) {
                    fwdTransferInProgress = 0;
                    for (int i = 0; i < 4; i++) {
                        this->mainTransferSrc[i] = false;
                        this->mainTransferDest[i] = false;
                    }
                }
            }
        }
        else { //if thresholds are different
            if (fwdTransferInProgress == 1) { //if is NOT trim transfer
                int indexes[4] = {0, 3, 1, 2};
                bool stop2[2] = {false, false};

                for (int j = 0; j < 2; j++) {

                    for (int i = 0; i < 2; i++) {
                        if (this->tankLevels[this->feedTks[indexes[2*j+i]]] > threshold14 + 1000)
                            stop2[j] = true;
                    }
                    if (stop2[j]) {
                        for (int i = 0; i < 2; i++) {
                            this->mainTransferDest[indexes[2*j+i]] = false;
                        }
                    }
                }
                if (stop2[0] && stop2[1]) { //only if both pairs of feed tanks are full, we stop the main transfer
                    fwdTransferInProgress = 0;
                    for (int i = 0; i < 4; i++)
                        this->mainTransferSrc[i] = false;
                }
            }
        }
    }

    void FQMS::checkMainTransfers(int remMinutes) {
        this->updateThresholds(remMinutes);
        this->checkMainTStop();
        this->checkMainTStart();
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

        for (int i = 0; i< 15; i++) {
            double diff = (1.0 * directRead[i]) / (1.0 * fqdcRead[i]);
            if (diff < 0.98 || diff > 1.02) {
                //exception maybe, is failure
            }
            this->tankLevels[i] = fqdcRead[i];
        }
    }

    void FQMS::updateThresholds(int remainMinutes) {

        if (this->tankLevels[3] + this->tankLevels[6] > 200 ||  //if transfer is from inner tanks
                this->tankLevels[2] + this->tankLevels[7] > 8000) { //or from mid tanks with more than 8000kg
            if (remainMinutes > 90) {
                this->threshold14 = 19560;
                this->threshold23 = 20840;
                return;
            }else {
                this->threshold14 = 16560;
                this->threshold23 = 17840;
                return;
            }
        }

        if (this->tankLevels[2] + this->tankLevels[7] > 200) { //if transfer is from mid tanks (with less than 8000kg)
            this->threshold14 = 19560;
            this->threshold23 = 19560;
            return;
        }
        if (this->tankLevels[10] > 200) { //if transfer is from trim tank
            this->threshold14 = 6000;
            this->threshold23 = 6000;
            return;
        }
        if (this->tankLevels[0] + this->tankLevels[9] > 100) { //if transfer is from outer tanks
            this->threshold14 = 4000;
            this->threshold23 = 4000;
            return;
        }
        this->threshold14 = 4000000; //if all tanks are empty, dont start any more transfers
        this->threshold23 = 4000000;
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
        for (int i = 0; i<40; i++) {
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
        for (int i = 0; i< 40; i++) {
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

}