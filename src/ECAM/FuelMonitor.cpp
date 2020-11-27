#include "FuelMonitor.h"


namespace ECAM {

    FuelMonitor::FuelMonitor(ECAMDataCache* edc) {
        this->ecamDataCache = edc;
        this->planeSysFe = nullptr;

        this->tempPmpsBtns = (bool*) malloc(20*sizeof(bool));
        this->tempLPSts = (bool*) malloc(5*sizeof(bool));

        this->gravVlvsAux = (int*) malloc(10*sizeof(int));
        this->gravVlvsAux[0] = 0; this->gravVlvsAux[1] = 1; this->gravVlvsAux[2] = 2; this->gravVlvsAux[3] = 3;
        this->gravVlvsAux[4] = 16; this->gravVlvsAux[5] = 17; this->gravVlvsAux[6] = 18; this->gravVlvsAux[7] = 19;
        this->gravVlvsAux[8] = 20; this->gravVlvsAux[9] = 21;

    }

    void FuelMonitor::setSystemsFEs(PluginControl::PlaneSystemsFrontends *pfe) {
        this->planeSysFe = pfe;
    }


    void FuelMonitor::updateFrontend() {
        //TODO get btns from cockpit frontend
        //TODO get lp vlvs from eng and apu frontend
        for(int i=0; i<20; i++)
            this->tempPmpsBtns[i] = true;

        for(int i=0; i<5; i++)
            this->tempLPSts[i] = true;



        //calculate and update frontend

        //tanks
        this->planeSysFe->ecamFe->setTankQuantities(this->ecamDataCache->FUELTkLevels);

        //pumps
        int pmps[21];
        for (int i=0; i<21; i++)
            pmps[i] = getPumpStateECAM(i);
        this->planeSysFe->ecamFe->setPmpStates(pmps);


    }




    int FuelMonitor::getPumpStateECAM(int id) {
        if (this->ecamDataCache->FUELPmpFailSts[id] == 0 && this->tempPmpsBtns[id]) {
            if(this->ecamDataCache->FUELPmpCommSts)
                return 1; //pump running
            return 0; //pump off
        }
        return 3;
        //4 (abnOn) and 5 (LO)  are not implemented
    }

    //failVlvArray: {0 = normal; 1 = Failed open; 2 = Failed closed
    //valves IDs: 0-4 - Consumers (0-3 Eng, 4 APU)
    //            5-24 - Wing tks (left->right) Fwd/Aft In
    //            25    - Trim tk In
    //            26-35 - Wing tks (left->right) Fwd/Aft Out
    //            34-35 - Trim tk out
    //            36-37 - Jettison

    int FuelMonitor::getEngLPStateECAM(int id) {
        //id = [0, 3]
        if (this->ecamDataCache->FUELVlvFailSts[id+40] == 1 && !this->tempLPSts[id]) {
            return 1; //Abn Open
        }
        if (this->ecamDataCache->FUELVlvFailSts[id+40] == 2 || (this->ecamDataCache->FUELVlvFailSts[id+40] == 0 && !this->tempLPSts[id])) {
            return 2; //Norm/Abn Closed
        }
        return 0; //Open
    }

    int FuelMonitor::getAPUFeedStateECAM() {
        if ((this->ecamDataCache->FUELVlvFailSts[44] == 0 || this->ecamDataCache->FUELVlvFailSts[44] == 2) && !this->tempLPSts[4]) {
            return 0; //Normal not fed
        }
        if (this->ecamDataCache->FUELVlvFailSts[44] == 1 && !this->tempLPSts[4]) {
            return 2; //Abn Fed
        }
        if (this->ecamDataCache->FUELVlvFailSts[44] == 2 && this->tempLPSts[4]) {
            return 3; //Abn Closed
        }
        return 1; //Normal Fed
    }

    int FuelMonitor::getCrossfeedVlvsStateECAM(int id) {
        //id = [0, 3]
        if ((this->ecamDataCache->FUELVlvFailSts[id+30] == 2 || this->ecamDataCache->FUELVlvFailSts[id+30] == 0) && this->ecamDataCache->FUELVlvCommSts[id+30] == 0) {
            return 0; //Valve closed
        }
        if ((this->ecamDataCache->FUELVlvFailSts[id+30] == 1 || this->ecamDataCache->FUELVlvFailSts[id+30] == 0) && this->ecamDataCache->FUELVlvCommSts[id+30] != 0) {
            return 1; //Valve open
        }
        if (this->ecamDataCache->FUELVlvFailSts[id+30] == 2) {
            return 2; //Valve failed closed
        }
        if (this->ecamDataCache->FUELVlvFailSts[id+30] == 1) {
            return 3; //Valve failed open
        }
        return 0; //should never get here
    }

    int FuelMonitor::getTrimVlvStateECAM() {
        if (((this->ecamDataCache->FUELVlvFailSts[37] == 0 || this->ecamDataCache->FUELVlvFailSts[37] == 1) && this->ecamDataCache->FUELVlvCommSts[37] != 0) ||
            ((this->ecamDataCache->FUELVlvFailSts[38] == 0 || this->ecamDataCache->FUELVlvFailSts[38] == 1) && this->ecamDataCache->FUELVlvCommSts[38] != 0) ||
            ((this->ecamDataCache->FUELVlvFailSts[20] == 0 || this->ecamDataCache->FUELVlvFailSts[20] == 1) && this->ecamDataCache->FUELVlvCommSts[20] != 0) ||
            ((this->ecamDataCache->FUELVlvFailSts[21] == 0 || this->ecamDataCache->FUELVlvFailSts[21] == 1) && this->ecamDataCache->FUELVlvCommSts[21] != 0)) {
            return 0; //Not isolated
        }
        if (((this->ecamDataCache->FUELVlvFailSts[37] == 0 || this->ecamDataCache->FUELVlvFailSts[37] == 2) && this->ecamDataCache->FUELVlvCommSts[37] == 0) &&
            ((this->ecamDataCache->FUELVlvFailSts[38] == 0 || this->ecamDataCache->FUELVlvFailSts[38] == 2) && this->ecamDataCache->FUELVlvCommSts[38] == 0) &&
            ((this->ecamDataCache->FUELVlvFailSts[20] == 0 || this->ecamDataCache->FUELVlvFailSts[20] == 2) && this->ecamDataCache->FUELVlvCommSts[20] == 0) &&
            ((this->ecamDataCache->FUELVlvFailSts[21] == 0 || this->ecamDataCache->FUELVlvFailSts[21] == 2) && this->ecamDataCache->FUELVlvCommSts[21] == 0)) {
            return 1; //Isolated
        }
        if (((this->ecamDataCache->FUELVlvFailSts[37] == 1) && this->ecamDataCache->FUELVlvCommSts[37] == 0) ||
            ((this->ecamDataCache->FUELVlvFailSts[38] == 1) && this->ecamDataCache->FUELVlvCommSts[38] == 0) ||
            ((this->ecamDataCache->FUELVlvFailSts[20] == 1) && this->ecamDataCache->FUELVlvCommSts[20] == 0) ||
            ((this->ecamDataCache->FUELVlvFailSts[21] == 1) && this->ecamDataCache->FUELVlvCommSts[21] == 0)) {
            return 2; //Abn not isolated
        }
        return 3; //Abn isolated
    }

    int FuelMonitor::getTransferVlvsStateECAM(int id) {
        //id = [0, 20]
        //TODO check if case of valve 20 is working
        if (id == 20) {
            if ((this->ecamDataCache->FUELVlvFailSts[20] == 0 || this->ecamDataCache->FUELVlvFailSts[20] == 2) && (this->ecamDataCache->FUELVlvCommSts[20]==0 || this->ecamDataCache->FUELVlvCommSts[20]==2 || this->ecamDataCache->FUELVlvCommSts[20]==4) &&
                (this->ecamDataCache->FUELVlvFailSts[21] == 0 || this->ecamDataCache->FUELVlvFailSts[21] == 2) && (this->ecamDataCache->FUELVlvCommSts[21]==0 || this->ecamDataCache->FUELVlvCommSts[21]==2 || this->ecamDataCache->FUELVlvCommSts[21]==4)) {
                return 0; //no transfer
            }
            if ((this->ecamDataCache->FUELVlvFailSts[20] == 0 || this->ecamDataCache->FUELVlvFailSts[20] == 1) && this->ecamDataCache->FUELVlvCommSts[20]==1 &&
                (this->ecamDataCache->FUELVlvFailSts[21] == 0 || this->ecamDataCache->FUELVlvFailSts[21] == 1) && this->ecamDataCache->FUELVlvCommSts[21]==1) {
                return 1; //auto transfer
            }
            if (((this->ecamDataCache->FUELVlvFailSts[20] == 0 || this->ecamDataCache->FUELVlvFailSts[20] == 1) && this->ecamDataCache->FUELVlvCommSts[20]==3) ||
                ((this->ecamDataCache->FUELVlvFailSts[21] == 0 || this->ecamDataCache->FUELVlvFailSts[21] == 1) && this->ecamDataCache->FUELVlvCommSts[21]==3)) {
                return 2; //manual transfer
            }
            return 3;
        }

        if ((this->ecamDataCache->FUELVlvFailSts[id] == 0 || this->ecamDataCache->FUELVlvFailSts[id] == 2) && (this->ecamDataCache->FUELVlvCommSts[id]==0 || this->ecamDataCache->FUELVlvCommSts[id]==2 || this->ecamDataCache->FUELVlvCommSts[id]==4)) {
            return 0; //no transfer
        }
        if ((this->ecamDataCache->FUELVlvFailSts[id] == 0 || this->ecamDataCache->FUELVlvFailSts[id] == 1) && this->ecamDataCache->FUELVlvCommSts[id]==1) {
            return 1; //auto transfer
        }
        if ((this->ecamDataCache->FUELVlvFailSts[id] == 0 || this->ecamDataCache->FUELVlvFailSts[id] == 1) && this->ecamDataCache->FUELVlvCommSts[id]==3) {
            return 2; //manual transfer
        }
        return 3; //Abn transfer (how can this happen boy?)
    }

    int FuelMonitor::getGravVlvsStateECAM(int id) {
        int innId = this->gravVlvsAux[id];
        //id = [0, 9]
        if ((this->ecamDataCache->FUELVlvFailSts[innId] == 0 || this->ecamDataCache->FUELVlvFailSts[innId] == 2) && (this->ecamDataCache->FUELVlvCommSts[innId]==0 || this->ecamDataCache->FUELVlvCommSts[innId]==1 || this->ecamDataCache->FUELVlvCommSts[innId]==3)) {
            return 0; //no transfer
        }
        if ((this->ecamDataCache->FUELVlvFailSts[innId] == 0 || this->ecamDataCache->FUELVlvFailSts[innId] == 1) && this->ecamDataCache->FUELVlvCommSts[innId]==2) {
            return 1; //auto transfer
        }
        if ((this->ecamDataCache->FUELVlvFailSts[innId] == 0 || this->ecamDataCache->FUELVlvFailSts[innId] == 1) && this->ecamDataCache->FUELVlvCommSts[innId]==4) {
            return 2; //manual transfer
        }
        //TODO this will fuck up im sure
        return 3; //Abn transfer
    }

    int FuelMonitor::getEmergVlvStateECAM(int id) {
        //id = [0, 1]
        if ((this->ecamDataCache->FUELVlvFailSts[id + 28] == 0 || this->ecamDataCache->FUELVlvFailSts[id + 28] == 2) &&
            this->ecamDataCache->FUELVlvCommSts[id + 28] == 0) {
            return 0; //norm closed
        }
        if ((this->ecamDataCache->FUELVlvFailSts[id + 28] == 0 || this->ecamDataCache->FUELVlvFailSts[id + 28] == 1) &&
            (this->ecamDataCache->FUELVlvCommSts[id + 28] == 1 || this->ecamDataCache->FUELVlvCommSts[id + 28] == 3)) {
            return 1; //norm open
        }
        return 2; //abn closed/open
    }

}