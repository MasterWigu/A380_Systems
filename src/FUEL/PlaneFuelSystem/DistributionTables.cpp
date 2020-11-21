//
// Created by MasterWigu on 31/08/2020.
//

#include "DistributionTables.h"
#include "Tables/Tables.h"
#include <cstdlib>
#include <cmath>

namespace PlaneFuelSystem {

    DistributionTables::DistributionTables() {
        //PFQ = preselected fuel quantity = total fuel

        // trimFuel[x][y][z] -> x=weight class; y=ZFCG class; z=PFQ class
        this->trimFuel = (int***) malloc(4*sizeof(int**));
        for (int i = 0; i < 4; i++) {
            this->trimFuel[i] = (int**) malloc(15 * sizeof(int *));
            for (int j = 0; j < 15; j++) {
                this->trimFuel[i][j] = (int*) malloc(244 * sizeof(int));
            }
        }

        populateT0(this->trimFuel);
        populateT1(this->trimFuel);
        populateT2(this->trimFuel);
        populateT3(this->trimFuel);
    }

    int DistributionTables::calculateWeightIndex(int ZFW) {
        if (ZFW < 270000)
            return -1;
        if (ZFW <= 292500)
            return 0;
        if (ZFW <= 315000)
            return 1;
        if (ZFW <= 337500)
            return 2;
        return 3;
    }

    int DistributionTables::calculateZFCGClass(double CG) {
        int roundCG = (int) std::round(CG);

        if (roundCG < 29 || roundCG > 43)
            return -1;
        return roundCG-29;
    }

    int DistributionTables::calculatePFQClass(int PFQ) {
        //round PFQ to the thousands
        PFQ = PFQ + 500; //to make 47600 = 48000 and not 47000
        PFQ = (PFQ / 1000) * 1000;
        if (PFQ <= 47000)
            return 0;
        if (PFQ > 290000)
            PFQ = 290000;
        return (PFQ-47000)/1000;
    }

    int DistributionTables::calculateTrimFuel(int cPFQ) {
        return this->calculateTrimFuel(300000, cPFQ, 36.5);
    }

    int DistributionTables::calculateTrimFuel(int ZFW, int cPFQ, double ZFCG) {
        int table = this->calculateWeightIndex(ZFW);
        int ZFCGClass = this->calculateZFCGClass(ZFCG);
        int PFQClass = this->calculatePFQClass(cPFQ);

        return this->trimFuel[table][ZFCGClass][PFQClass];
    }

}
