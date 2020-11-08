//
// Created by morei on 06/10/2020.
//

#include "FQMS.h"

namespace PlaneFuelSystem {
/*
    void FQMS::processPmpFailuresECAM(int id) {
        switch (id) {
            case 0: { //feed 1 main
                this->ECAMProceduresNow[30] = true;
                if (this->ECAMProceduresNow[34])
                    this->ECAMProceduresNow[26] = true;
            }
            case 2: { //feed 2 main
                this->ECAMProceduresNow[31] = true;
                if (this->ECAMProceduresNow[35])
                    this->ECAMProceduresNow[27] = true;
            }
            case 4: { //feed 3 main
                this->ECAMProceduresNow[32] = true;
                if (this->ECAMProceduresNow[36])
                    this->ECAMProceduresNow[28] = true;
            }
            case 6: { //feed 4 main
                this->ECAMProceduresNow[33] = true;
                if (this->ECAMProceduresNow[37])
                    this->ECAMProceduresNow[29] = true;
            }
            case 1: { //feed 1 stby
                this->ECAMProceduresNow[34] = true;
                if (this->ECAMProceduresNow[30])
                    this->ECAMProceduresNow[26] = true;
            }
            case 3: { //feed 2 stby
                this->ECAMProceduresNow[35] = true;
                if (this->ECAMProceduresNow[31])
                    this->ECAMProceduresNow[27] = true;
            }
            case 5: { //feed 3 stby
                this->ECAMProceduresNow[36] = true;
                if (this->ECAMProceduresNow[32])
                    this->ECAMProceduresNow[28] = true;
            }
            case 7: { //feed 4 stby
                this->ECAMProceduresNow[37] = true;
                if (this->ECAMProceduresNow[33])
                    this->ECAMProceduresNow[29] = true;
            }

            case 12: { //L inr aft
                this->ECAMProceduresNow[59] = true;
                if (this->ECAMProceduresNow[63])
                    this->ECAMProceduresNow[57] = true;
            }
            case 14: { //R inr aft
                this->ECAMProceduresNow[60] = true;
                if (this->ECAMProceduresNow[64])
                    this->ECAMProceduresNow[58] = true;
            }
            case 11: { //L inr fwd
                this->ECAMProceduresNow[63] = true;
                if (this->ECAMProceduresNow[59])
                    this->ECAMProceduresNow[57] = true;
            }
            case 13: { //R inr fwd
                this->ECAMProceduresNow[64] = true;
                if (this->ECAMProceduresNow[60])
                    this->ECAMProceduresNow[58] = true;
            }

            case 10: { //L mid aft
                this->ECAMProceduresNow[61] = true;
                if (this->ECAMProceduresNow[65])
                    this->ECAMProceduresNow[67] = true;
            }
            case 16: { //R mid aft
                this->ECAMProceduresNow[62] = true;
                if (this->ECAMProceduresNow[66])
                    this->ECAMProceduresNow[68] = true;
            }
            case 9: { //L mid fwd
                this->ECAMProceduresNow[65] = true;
                if (this->ECAMProceduresNow[61])
                    this->ECAMProceduresNow[67] = true;
            }
            case 15: { //R mid fwd
                this->ECAMProceduresNow[66] = true;
                if (this->ECAMProceduresNow[62])
                    this->ECAMProceduresNow[68] = true;
            }

            case 8: { //L outer
                this->ECAMProceduresNow[69] = true;
            }
            case 17: { //R outer
                this->ECAMProceduresNow[70] = true;
            }


                //TODO add cases for transfer pumps
        }
    }

    void FQMS::processCumulativeECAMProc() {

        //FEED PMPs
        if (this->ECAMProceduresNow[30] && this->ECAMProceduresNow[34]) {
            this->ECAMProceduresNow[26] = true;
        }
        if (this->ECAMProceduresNow[31] && this->ECAMProceduresNow[35]) {
            this->ECAMProceduresNow[27] = true;
        }
        if (this->ECAMProceduresNow[32] && this->ECAMProceduresNow[36]) {
            this->ECAMProceduresNow[28] = true;
        }
        if (this->ECAMProceduresNow[33] && this->ECAMProceduresNow[37]) {
            this->ECAMProceduresNow[29] = true;
        }

        if (this->ECAMProceduresNow[26] && this->ECAMProceduresNow[27]) {
            this->ECAMProceduresNow[71] = true;
        }
        if (this->ECAMProceduresNow[28] && this->ECAMProceduresNow[29]) {
            this->ECAMProceduresNow[72] = true;
        }


        //TRANSFER PMPs
        if (this->ECAMProceduresNow[59] && this->ECAMProceduresNow[63]) {
            this->ECAMProceduresNow[57] = true;
        }
        if (this->ECAMProceduresNow[60] && this->ECAMProceduresNow[64]) {
            this->ECAMProceduresNow[58] = true;
        }

        if (this->ECAMProceduresNow[61] && this->ECAMProceduresNow[65]) {
            this->ECAMProceduresNow[67] = true;
        }
        if (this->ECAMProceduresNow[62] && this->ECAMProceduresNow[66]) {
            this->ECAMProceduresNow[68] = true;
        }

    }*/
}

