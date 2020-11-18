//
// Created by MasterWigu on 17/10/2020.
//

#include <cstring>
#include "F001_AllFeedLow.h"

namespace ECAM {
    F001_AllFeedLow::F001_AllFeedLow(PluginControl::PlaneSystemsRefs* systems) {
        this->planeSystems = systems;
        this->displayData = new ProcDisplayData();
        this->permInfo = new ProcPermInfo();

        //put all lines here!
        this->line1Under = (char*) malloc(5*sizeof(char));
        strcpy(this->line1Under, u8"FUEL");

        this->linesBefore = (char**) malloc(9*sizeof(char*));
        this->linesAfter = (char**) malloc(9*sizeof(char*));
        this->lineColors = (int*) malloc(9*sizeof(int));

        this->linesBefore[0] = (char*) malloc(22 * sizeof(char));
        this->linesAfter[0] = (char*) malloc(22 * sizeof(char));
        strcpy(this->linesBefore[0], u8"ALL FEED TKs LEVEL LO");
        strcpy(this->linesAfter[0], u8"ALL FEED TKs LEVEL LO");
        this->lineColors[0] = 4;

        this->linesBefore[1] = (char*) malloc(42 * sizeof(char));
        this->linesAfter[1] = (char*) malloc(42 * sizeof(char));
        strcpy(this->linesBefore[1], u8"                                LAND ANSA");
        strcpy(this->linesAfter[1], u8"                                LAND ANSA");
        this->lineColors[1] = 4;

        this->linesBefore[2] = (char*) malloc(42 * sizeof(char));
        this->linesAfter[2] = (char*) malloc(20 * sizeof(char));
        strcpy(this->linesBefore[2], u8"  ALL CROSSFEEDs.......................ON");
        strcpy(this->linesAfter[2], u8"  ALL CROSSFEEDs ON");
        this->lineColors[2] = 2;

        this->linesBefore[3] = (char*) malloc(42 * sizeof(char));
        this->linesAfter[3] = (char*) malloc(23 * sizeof(char));
        strcpy(this->linesBefore[3], u8"  ALL FEED TKs PMPs....................ON");
        strcpy(this->linesAfter[3], u8"  ALL FEED TKs PMPs ON");
        this->lineColors[3] = 2;

        this->linesBefore[4] = (char*) malloc(42 * sizeof(char));
        this->linesAfter[4] = (char*) malloc(20 * sizeof(char));
        strcpy(this->linesBefore[4], u8"  TRIM TK FEED.......................AUTO");
        strcpy(this->linesAfter[4], u8"  TRIM TK FEED AUTO");
        this->lineColors[4] = 2;

        this->linesBefore[5] = (char*) malloc(42 * sizeof(char));
        this->linesAfter[5] = (char*) malloc(18 * sizeof(char));
        strcpy(this->linesBefore[5], u8"  OUTR TK XFR.........................MAN");
        strcpy(this->linesAfter[5], u8"  OUTR TK XFR MAN");
        this->lineColors[5] = 2;

        this->linesBefore[6] = (char*) malloc(42 * sizeof(char));
        this->linesAfter[6] = (char*) malloc(18 * sizeof(char));
        strcpy(this->linesBefore[6], u8"  TRIM TK XFR.........................FWD");
        strcpy(this->linesAfter[6], u8"  TRIM TK XFR FWD");
        this->lineColors[6] = 2;

        this->linesBefore[7] = (char*) malloc(42 * sizeof(char));
        this->linesAfter[7] = (char*) malloc(17 * sizeof(char));
        strcpy(this->linesBefore[7], u8"  INR TK XFR..........................MAN");
        strcpy(this->linesAfter[7], u8"  INR TK XFR MAN");
        this->lineColors[7] = 2;

        this->linesBefore[8] = (char*) malloc(42 * sizeof(char));
        this->linesAfter[8] = (char*) malloc(17 * sizeof(char));
        strcpy(this->linesBefore[8], u8"  MID TK XFR..........................MAN");
        strcpy(this->linesAfter[8], u8"  MID TK XFR MAN");
        this->lineColors[8] = 2;


        //clear procedure (leave here, CHANGE just index in arrays)
        this->linesBefore[9] = (char*) malloc(43 * sizeof(char));
        this->linesAfter[9] = (char*) malloc(43 * sizeof(char));
        strcpy(this->linesBefore[9], u8"☐                                   CLEAR");
        strcpy(this->linesAfter[9], u8"☑                                   CLEAR");
        this->lineColors[9] = 2;



        //Put limitations, etc. here
        this->limitations = (char**) malloc(sizeof(char*));
        this->limitations[0] = (char*) malloc(10*sizeof(char));
        strcpy(this->limitations[0], u8"LAND ANSA");

    }

    bool F001_AllFeedLow::testProcedure() {
        double* levels = nullptr; //this->planeSystems->fuelSystem->getTankLevels();

        //put condition(s) here!
        if (levels[1] < 1375 && levels[4] < 1375 && levels[5] < 1375 && levels[8] < 1375) {

        //pls dont change this
            if (!this->permInfo->active)
                this->displayData->cleared = false;
            this->displayData->active = true;
            this->permInfo->active = true;
            return true;
        }

        this->displayData->active = false;
        this->permInfo->active = false;
        this->displayData->cleared = true;
        return false;
    }



    bool F001_AllFeedLow::showProcedure(int linesToShow, bool selected, bool lastLineTicked) {
        int* fuelBtns = this->planeSystems->cockpitControls->getFuelButtons();
        double* tkQty;

        int lines = 0;
        if (linesToShow == 0)
            return false;

        this->displayData->line1Under = this->line1Under;
        this->displayData->linesText[0] = this->linesAfter[0];
        this->displayData->lineColors[0] = 4; //amber
        if (selected && this->displayData->selectedLine < lines) {
            this->displayData->selectedLine++;
            selected = false;
        }
        lines++;
        if (linesToShow == lines)
            return true;


        if (this->displayData->selectedLine < linesToShow) {
            this->displayData->linesText[lines] = this->linesAfter[1]; //land ansa
            this->displayData->lineColors[lines] = 4; //amber
            if (selected && this->displayData->selectedLine < lines) {
                this->displayData->selectedLine++;
                selected = false;
            }
            lines++;
        }
        if (linesToShow == lines)
            return true;


        if (this->displayData->selectedLine < linesToShow) {
            if (!(fuelBtns[0] == 1 && fuelBtns[1] == 1 && fuelBtns[2] == 1 && fuelBtns[3] == 1)) {
                this->displayData->linesText[lines] = this->linesBefore[2]; //crossfeed open
                this->displayData->lineColors[lines] = 2; //blue
            }
            else {
                this->displayData->linesText[lines] = this->linesAfter[2];
                this->displayData->lineColors[lines] = 0; //white
                if (selected && this->displayData->selectedLine < lines)
                    this->displayData->selectedLine++;
            }
            lines++;
        }
        if (linesToShow == lines)
            return true;


        if (this->displayData->selectedLine < linesToShow) {
            if (!(fuelBtns[4] == 1 && fuelBtns[5] == 1 && fuelBtns[6] == 1 && fuelBtns[7] == 1 &&
                    fuelBtns[8] == 1 && fuelBtns[9] == 1 && fuelBtns[10] == 1 && fuelBtns[11] == 1)) {
                this->displayData->linesText[lines] = this->linesBefore[3]; //feed pmps on
                this->displayData->lineColors[lines] = 2; //blue
            }
            else {
                this->displayData->linesText[lines] = this->linesAfter[3];
                this->displayData->lineColors[lines] = 0; //white
                if (selected && this->displayData->selectedLine < lines)
                    this->displayData->selectedLine++;
            }
            lines++;
        }
        if (linesToShow == lines)
            return true;


        if (true) { //if grav transfer from trim in progress TODO create on frontend
            if (this->displayData->selectedLine < linesToShow) {
                if (fuelBtns[28] != 1) {
                    this->displayData->linesText[lines] = this->linesBefore[4]; //trim tk feed not auto yet
                    this->displayData->lineColors[lines] = 2; //blue
                } else {
                    this->displayData->linesText[lines] = this->linesAfter[4];
                    this->displayData->lineColors[lines] = 0; //white
                    if (selected && this->displayData->selectedLine < lines)
                        this->displayData->selectedLine++;
                }
                lines++;
            }
            if (linesToShow == lines)
                return true;
        }


        tkQty = nullptr;//this->planeSystems->fuelSystem->getTankLevels();

        if (tkQty[0] > 100 || tkQty[9] > 100) { //if outer has fuel
            if (this->displayData->selectedLine < linesToShow) {
                if (fuelBtns[24] != 1) {
                    this->displayData->linesText[lines] = this->linesBefore[5]; //outer tk xfx not man
                    this->displayData->lineColors[lines] = 2; //blue
                } else {
                    this->displayData->linesText[lines] = this->linesAfter[5];
                    this->displayData->lineColors[lines] = 0; //white
                    if (selected && this->displayData->selectedLine < lines)
                        this->displayData->selectedLine++;
                }
                lines++;
            }
            if (linesToShow == lines)
                return true;


            if (true) { //if at least one trim pmp running TODO create on frontend
                if (this->displayData->selectedLine < linesToShow) {
                    if (fuelBtns[27] != 1) {
                        this->displayData->linesText[lines] = this->linesBefore[6]; //trim tk xfx not fwd
                        this->displayData->lineColors[lines] = 2; //blue
                    } else {
                        this->displayData->linesText[lines] = this->linesAfter[6];
                        this->displayData->lineColors[lines] = 0; //white
                        if (selected && this->displayData->selectedLine < lines)
                            this->displayData->selectedLine++;
                    }
                    lines++;
                }
                if (linesToShow == lines)
                    return true;
            }
        }


        if (tkQty[3] > 100 || tkQty[6] > 100) { //if inr has fuel
            if (this->displayData->selectedLine < linesToShow) {
                if (fuelBtns[26] != 1) {
                    this->displayData->linesText[lines] = this->linesBefore[7]; //inr tk xfx not man
                    this->displayData->lineColors[lines] = 2; //blue
                } else {
                    this->displayData->linesText[lines] = this->linesAfter[7];
                    this->displayData->lineColors[lines] = 0; //white
                    if (selected && this->displayData->selectedLine < lines)
                        this->displayData->selectedLine++;
                }
                lines++;
            }
            if (linesToShow == lines)
                return true;
        }

        if (tkQty[2] > 100 || tkQty[7] > 100) { //if mid has fuel
            if (this->displayData->selectedLine < linesToShow) {
                if (fuelBtns[25] != 1) {
                    this->displayData->linesText[lines] = this->linesBefore[8]; //mid tk xfx not man
                    this->displayData->lineColors[lines] = 2; //blue
                } else {
                    this->displayData->linesText[lines] = this->linesAfter[8];
                    this->displayData->lineColors[lines] = 0; //white
                    if (selected && this->displayData->selectedLine < lines)
                        this->displayData->selectedLine++;
                }
                lines++;
            }
            if (linesToShow == lines)
                return true;
        }

        this->displayData->numberLines = lines;
        return true;
    }

    bool F001_AllFeedLow::getPermInfo() {
        this->permInfo->ecamLimitAll[0] = this->limitations[0];
        this->permInfo->nEcamLimitAll = 1;
        return true;
    }
}
