//
// Created by morei on 01/09/2020.
//
#include "FQMS.h"

namespace PlaneFuelSystem {
    FQMS::FQMS(FuelSystem::FuelSystem* fS, PlaneFuelSystem::FQDC* f, PlaneFuelSystem::FuelSystemFronend* sFE) {
        this->fuelSystem = fS;
        this->fqdc = f;
        this->fronend = sFE;
        this->arraysInit();

        this->templates = new TemplateGetter();

        this->fwdOccupied = false;
        this->aftOccupied = false;

        this->feedTks = (int *) malloc(4 * sizeof(int));
        this->feedTks[0] = 1; this->feedTks[1] = 4;this->feedTks[2] = 5;this->feedTks[3] = 8;

        this->emergValvesCockpit = false;

        this->inFlight = false;
        this->CGTarget = 0;
        this->FL = 0;
        this->simTime = -1;
        this->lastSimTime = -1;
        this->flWasAbove255 = false;

    }

    void FQMS::arraysInit() {
        //NOTE: case 4 is two cases, for mid or inner, that makes a total of 7 cases instead of 6
        this->abnCases = (bool *) malloc(7 * sizeof(bool));
        for (int i = 0; i < 7; i++)
            this->abnCases[i] = false;

        this->tankLevels = (int *) malloc(15 * sizeof(int));
        for (int i = 0; i < 6; i++)
            this->tankLevels[i] = 0;

        this->commandedPumpStates = (bool* ) malloc(21 * sizeof(bool));
        for (int i = 0; i < 21; i++)
            this->commandedPumpStates[i] = false;

        //commVlvStates: 0-Closed, 1-Open, 2-GravOpen, 3-Manual Open, 4-Manual Grav Open
        this->commandedVlvStates = (int* ) malloc(39 * sizeof(int));
        for (int i = 0; i < 39; i++)
            this->commandedVlvStates[i] = 0;

        this->pumpsFailStates = (int*) malloc(21*sizeof(int));
        for (int i = 0; i < 21; i++)
            this->pumpsFailStates[i] = 0;

        this->vlvsFailStates = (int*) malloc(47*sizeof(int));
        for (int i = 0; i < 47; i++)
            this->vlvsFailStates[i] = 0;

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

        this->requestedLPValves = (bool*) malloc(5 * sizeof(bool));
        for (int i = 0; i < 5; i++)
            this->requestedLPValves[i] = false;

        this->ECAMProceduresNow = (bool*) malloc(104 * sizeof(bool));
        for (int i = 0; i < 104; i++)
            this->ECAMProceduresNow[i] = false;

        this->ECAMProceduresPrevious = (bool*) malloc(104 * sizeof(bool));
        for (int i = 0; i < 104; i++)
            this->ECAMProceduresPrevious[i] = false;


        this->gravVlvsAux = (int*) malloc(10*sizeof(int));
        this->gravVlvsAux[0] = 0; this->gravVlvsAux[1] = 1; this->gravVlvsAux[2] = 2; this->gravVlvsAux[3] = 3;
        this->gravVlvsAux[4] = 16; this->gravVlvsAux[5] = 17; this->gravVlvsAux[6] = 18; this->gravVlvsAux[7] = 19;
        this->gravVlvsAux[8] = 20; this->gravVlvsAux[9] = 21;
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
            this->vlvsFailStates[45] == 1 || this->vlvsFailStates[46] == 1) { //jettison valves


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

    void FQMS::updateLoop(int remMinutes, int GW, double currCG, float simulatorTime, int f) {
        this->FL = f;

        if (this->lastSimTime == -1)
            this->lastSimTime = simulatorTime;
        else
            this->lastSimTime = this->simTime;
        this->simTime = simulatorTime;

        if (f > 2) //TODO temporary, assume inFlight = above 2000ft
            this->inFlight = true;
        else
            this->inFlight = false;

        this->updateTimers(remMinutes, f);


        //Reset ecam proc
        bool* temp = this->ECAMProceduresNow;
        this->ECAMProceduresNow = this->ECAMProceduresPrevious;
        this->ECAMProceduresPrevious = temp;

        for (int i = 0; i<103; i++) {
            this->ECAMProceduresNow[i] = false;
        }

        this->updateCGTarget(GW);
        this->getTankLevels();
        this->detectAbnCases();
        this->selectTransfers(remMinutes, currCG);
        this->applyTransfers();

        this->applyState();
        this->reportECAMProc();

    }

    void FQMS::updateTimers(int remMinutes, int f) {
        float deltaTime = this->simTime - this->lastSimTime;

        //Update lever timers
        if (f > 245)
            this->timeBlwFL245 = 0;
        else
            this->timeBlwFL245 += deltaTime;

        if (f < 255)
            this->timeAbvFL255 = 0;
        else {
            this->timeAbvFL255 += deltaTime;
            this->flWasAbove255 = true;
        }


        //Update time remaining timers
        if (remMinutes > 30)
            this->time30min = 0;
        else
            this->time30min += deltaTime;

        if (remMinutes > 80)
            this->time80min = 0;
        else
            this->time80min += deltaTime;

    }

    void FQMS::updateCGTarget(int GW) {
        double GWt = GW / 1000.0;
        this->CGTarget = (5058.4908643318586 + sqrt(25588329.824528873888 - 253.782771599910176 * (101088.31599889736 - GWt))) / 126.891385799955088;
    }

    void FQMS::selectTransfers(int remFltTime, double currCG) {
        if (this->abnCases[7])
            return; //if we have too many failures, no automatic transfers are possible
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
        if (this->FL > 3 && this->FOB > 50000 && this->tankLevels[0]+ this->tankLevels[9] < 16230) { //if fob>50t && outer not full
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
        if (this->time80min > 150 && (this->flWasAbove255 && this->timeBlwFL245 > 60) &&  !aftOccupied  && this->tankLevels[10] > 100 || //Start
            this->lastTransfers[10] && this->tankLevels[10] > 100) { //continue (not all stop conditions are verified
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
        if (!fwdOccupied && (this->tankLevels[0] > 4000 || this->tankLevels[9] > 4000) && this->time30min > 150 && (this->flWasAbove255 && this->timeBlwFL245 > 60)) { //not all stop conditions are verified
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


    void FQMS::applyTransfers() {
        int **result;
        for (int i = 0; i < 14; i++) {
                    if (this->commandedTransfers[i]) {
                        result = this->templates->getTemplate(i, this->tankLevels, this->pumpsFailStates, this->vlvsFailStates,
                                                      this->abnCases, true, false);

                if (result != nullptr) {
                    for  (int j = 0; j < 21; j++) {
                        this->commandedPumpStates[j] = result[0][j] == 1;
                    }
                    for  (int j = 0; j < 39; j++) {
                        this->commandedVlvStates[j] = result[1][j];
                    }
                }
            }
        }
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




        //Collector cells - appear || maintain (before >940kg)
        if (this->tankLevels[11] < 780 || (this->ECAMProceduresPrevious[9] && this->tankLevels[11] < 940)) {
            this->ECAMProceduresNow[9] = true;
        }
        if (this->tankLevels[12] < 780 || (this->ECAMProceduresPrevious[10] && this->tankLevels[12] < 940)) {
            this->ECAMProceduresNow[10] = true;
        }
        if (this->tankLevels[13] < 780 || (this->ECAMProceduresPrevious[11] && this->tankLevels[13] < 940)) {
            this->ECAMProceduresNow[11] = true;
        }
        if (this->tankLevels[14] < 780 || (this->ECAMProceduresPrevious[12] && this->tankLevels[14] < 940)) {
            this->ECAMProceduresNow[12] = true;
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
                this->processPmpFailuresECAM(i);
            }
        }
    }

    void FQMS::applyValveState() {
        for (int i = 0; i< 39; i++) {
            if (i > 21 && i < 28) continue;

            this->fuelSystem->setValveState(i, this->commandedVlvStates[i] ? 1 : 0);
            if (this->fuelSystem->readValveState(i) != (this->commandedVlvStates[i] ? 1 : 0)) { //if valve is failed
                if (this->fuelSystem->readValveState(i) == 1) //if valve is open
                    this->vlvsFailStates[i] = 1; //failed open
                else                                        //else if valve is closed
                    this->vlvsFailStates[i] = 2; //failed closed
            }
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

    //failVlvArray: {0 = normal; 1 = Failed open; 2 = Failed closed
    //valves IDs: 0-4 - Consumers (0-3 Eng, 4 APU)
    //            5-24 - Wing tks (left->right) Fwd/Aft In
    //            25    - Trim tk In
    //            26-35 - Wing tks (left->right) Fwd/Aft Out
    //            34-35 - Trim tk out
    //            36-37 - Jettison

    int FQMS::getEngLPStateECAM(int id) {
        //id = [0, 3]
        if (this->vlvsFailStates[id+40] == 1 && !this->requestedLPValves[id]) {
            return 1; //Abn Open
        }
        if (this->vlvsFailStates[id+40] == 2 || (this->vlvsFailStates[id+40] == 0 && !this->requestedLPValves[id])) {
            return 2; //Norm/Abn Closed
        }
        return 0; //Open
    }

    int FQMS::getAPUFeedStateECAM() {
        if ((this->vlvsFailStates[44] == 0 || this->vlvsFailStates[44] == 2) && !this->requestedLPValves[4]) {
            return 0; //Normal not fed
        }
        if (this->vlvsFailStates[44] == 1 && !this->requestedLPValves[4]) {
            return 2; //Abn Fed
        }
        if (this->vlvsFailStates[44] == 2 && this->requestedLPValves[4]) {
            return 3; //Abn Closed
        }
        return 1; //Normal Fed
    }

    int FQMS::getCrossfeedVlvsStateECAM(int id) {
        //id = [0, 3]
        if ((this->vlvsFailStates[id+30] == 2 || this->vlvsFailStates[id+30] == 0) && this->commandedVlvStates[id+30] == 0) {
            return 0; //Valve closed
        }
        if ((this->vlvsFailStates[id+30] == 1 || this->vlvsFailStates[id+30] == 0) && this->commandedVlvStates[id+30] != 0) {
            return 1; //Valve open
        }
        if (this->vlvsFailStates[id+30] == 2) {
            return 2; //Valve failed closed
        }
        if (this->vlvsFailStates[id+30] == 1) {
            return 3; //Valve failed open
        }
        return 0; //should never get here
    }

    int FQMS::getTrimVlvStateECAM() {
        if (((this->vlvsFailStates[37] == 0 || this->vlvsFailStates[37] == 1) && this->commandedVlvStates[37] != 0) ||
                ((this->vlvsFailStates[38] == 0 || this->vlvsFailStates[38] == 1) && this->commandedVlvStates[38] != 0) ||
                ((this->vlvsFailStates[20] == 0 || this->vlvsFailStates[20] == 1) && this->commandedVlvStates[20] != 0) ||
                ((this->vlvsFailStates[21] == 0 || this->vlvsFailStates[21] == 1) && this->commandedVlvStates[21] != 0)) {
            return 0; //Not isolated
        }
        if (((this->vlvsFailStates[37] == 0 || this->vlvsFailStates[37] == 2) && this->commandedVlvStates[37] == 0) &&
            ((this->vlvsFailStates[38] == 0 || this->vlvsFailStates[38] == 2) && this->commandedVlvStates[38] == 0) &&
            ((this->vlvsFailStates[20] == 0 || this->vlvsFailStates[20] == 2) && this->commandedVlvStates[20] == 0) &&
            ((this->vlvsFailStates[21] == 0 || this->vlvsFailStates[21] == 2) && this->commandedVlvStates[21] == 0)) {
            return 1; //Isolated
        }
        if (((this->vlvsFailStates[37] == 1) && this->commandedVlvStates[37] == 0) ||
            ((this->vlvsFailStates[38] == 1) && this->commandedVlvStates[38] == 0) ||
            ((this->vlvsFailStates[20] == 1) && this->commandedVlvStates[20] == 0) ||
            ((this->vlvsFailStates[21] == 1) && this->commandedVlvStates[21] == 0)) {
            return 2; //Abn not isolated
        }
        return 3; //Abn isolated
    }

    int FQMS::getTransferVlvsStateECAM(int id) {
        //id = [0, 20]
        //TODO check if case of valve 20 is working
        if (id == 20) {
            if ((this->vlvsFailStates[20] == 0 || this->vlvsFailStates[20] == 2) && (this->commandedVlvStates[20]==0 || this->commandedVlvStates[20]==2 || this->commandedVlvStates[20]==4) &&
                    (this->vlvsFailStates[21] == 0 || this->vlvsFailStates[21] == 2) && (this->commandedVlvStates[21]==0 || this->commandedVlvStates[21]==2 || this->commandedVlvStates[21]==4)) {
                return 0; //no transfer
            }
            if ((this->vlvsFailStates[20] == 0 || this->vlvsFailStates[20] == 1) && this->commandedVlvStates[20]==1 &&
                    (this->vlvsFailStates[21] == 0 || this->vlvsFailStates[21] == 1) && this->commandedVlvStates[21]==1) {
                return 1; //auto transfer
            }
            if ((this->vlvsFailStates[20] == 0 || this->vlvsFailStates[20] == 1) && this->commandedVlvStates[20]==3 ||
                    (this->vlvsFailStates[21] == 0 || this->vlvsFailStates[21] == 1) && this->commandedVlvStates[21]==3) {
                return 2; //manual transfer
            }
            return 3;
        }

        if ((this->vlvsFailStates[id] == 0 || this->vlvsFailStates[id] == 2) && (this->commandedVlvStates[id]==0 || this->commandedVlvStates[id]==2 || this->commandedVlvStates[id]==4)) {
            return 0; //no transfer
        }
        if ((this->vlvsFailStates[id] == 0 || this->vlvsFailStates[id] == 1) && this->commandedVlvStates[id]==1) {
            return 1; //auto transfer
        }
        if ((this->vlvsFailStates[id] == 0 || this->vlvsFailStates[id] == 1) && this->commandedVlvStates[id]==3) {
            return 2; //manual transfer
        }
        return 3; //Abn transfer (how can this happen boy?)
    }

    int FQMS::getGravVlvsStateECAM(int id) {
        int innId = this->gravVlvsAux[id];
        //id = [0, 9]
        if ((this->vlvsFailStates[innId] == 0 || this->vlvsFailStates[innId] == 2) && (this->commandedVlvStates[innId]==0 || this->commandedVlvStates[innId]==1 || this->commandedVlvStates[innId]==3)) {
            return 0; //no transfer
        }
        if ((this->vlvsFailStates[innId] == 0 || this->vlvsFailStates[innId] == 1) && this->commandedVlvStates[innId]==2) {
            return 1; //auto transfer
        }
        if ((this->vlvsFailStates[innId] == 0 || this->vlvsFailStates[innId] == 1) && this->commandedVlvStates[innId]==4) {
            return 2; //manual transfer
        }
        //TODO this will fuck up im sure
        return 3; //Abn transfer
    }

    int FQMS::getEmergVlvStateECAM(int id) {
        //id = [0, 1]
        if ((this->vlvsFailStates[id+28] == 0 || this->vlvsFailStates[id+28] == 2) && this->commandedVlvStates[id+28]==0) {
            return 0; //norm closed
        }
        if ((this->vlvsFailStates[id+28] == 0 || this->vlvsFailStates[id+28] == 1) && (this->commandedVlvStates[id+28]==1 || this->commandedVlvStates[id+28]==3)) {
            return 1; //norm open
        }
    return 2; //abn closed/open
    }


    void FQMS::reportECAMProc() {
        for (int i=0; i<103; i++) {
            if (this->ECAMProceduresNow[i] == this->ECAMProceduresPrevious[i]) {
                continue;
            }
            else if (this->ECAMProceduresNow[i]) {
                //report true
            }
            else {
                //report false
            }
        }
    }
}