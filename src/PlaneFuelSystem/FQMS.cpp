//
// Created by morei on 01/09/2020.
//
#include <cstdlib>
#include "FQMS.h"


namespace PlaneFuelSystem {
    FQMS::FQMS(FuelSystem::FuelSystem* fS, PlaneFuelSystem::FQDC* f) {
        this->fuelSystem = fS;
        this->fqdc = f;

        this->fwdTransferInProgress = -1;
        this->aftTransferInProgress = -1;

        this->mainTransferDest = (bool*) malloc(4*sizeof(bool));
        for (int i = 0; i < 4; i++)
            this->mainTransferDest[i] = false;

        this->mainTransferSrc = (bool*) malloc(4*sizeof(bool));
        for (int i = 0; i < 4; i++)
            this->mainTransferSrc[i] = false;


        this->abnCases = (bool *) malloc(6 * sizeof(bool));
        for (int i = 0; i < 6; i++)
            this->abnCases[i] = false;

        this->tankLevels = (int *) malloc(15 * sizeof(int));
        for (int i = 0; i < 6; i++)
            this->tankLevels[i] = 0;



        this->threshold14 = 19560;
        this->threshold23 = 20840;
        this->feedTks = (int *) malloc(4 * sizeof(int));
        this->feedTks[0] = 1; this->feedTks[1] = 4;this->feedTks[2] = 5;this->feedTks[3] = 8;
    }

    //Possible transfers: 1 - Main - Any   -> Any   (fwd/aft for trim) Done
    //                    8 - Load - Inner -> Outer (fwd)
    //                    9 - Load - Mid   -> Outer (fwd)
    //                    10- Load - Trim  -> Feed  (aft)
    //                    11- Load - Trim  -> Mid   (aft)
    //                    12- Load - Trim  -> Inner (aft)
    //                    13- Load - Outer -> Feed  (fwd)
    //                    14- Load - Outer -> Mid   (fwd)
    //                    15- Load - Outer -> Inner (fwd)
    //                    16- CG   - Trim  -> Inner (aft)
    //                    17- CG   - Trim  -> Mid   (aft)
    //                    18- CG   - Trim  -> Feed  (aft)
    //                    19- Cold - Outer -> Feed  (fwd)
    //                    20- Cold - Outer -> Mid   (fwd)
    //                    21- Cold - Outer -> Inner (fwd)

    void FQMS::updateLoop(int remMinutes) {
        this->getTankLevels();
        this->checkMainTransfers(remMinutes);

    }

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


}