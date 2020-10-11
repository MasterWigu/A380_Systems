//
// Created by morei on 01/09/2020.
//

#include "FuelDistributor.h"
#include <cstdlib>
#include <cmath>

namespace PlaneFuelSystem {

    FuelDistributor::FuelDistributor() {
        this->distributionTables = new DistributionTables();
    }

    int* FuelDistributor::wingDistributor(int wingFuel) {
        int* tanks = (int*) malloc(11*sizeof(int));
        //0: left outer; 1: left feed 1; 2: left mid; 3: left inner; 4: left feed 2
        //5: right feed 3; 6: right inner; 7: right mid; 8: right feed 4; 9: right outer
        //10 - trim tank
        for (int i = 0; i < 11; i++)
            tanks[i] = 0;

        if (wingFuel <= 18000) { //<A
            tanks[1] = wingFuel / 4;
            tanks[4] = wingFuel / 4;
            tanks[5] = wingFuel / 4;
            tanks[8] = wingFuel / 4;
            return tanks;
        }
        if (wingFuel <= 26000) { //A-B
            tanks[1] = 4500;
            tanks[4] = 4500;
            tanks[5] = 4500;
            tanks[8] = 4500;
            tanks[0] = (wingFuel - 18000) / 2;
            tanks[9] = (wingFuel - 18000) / 2;
            return tanks;
        }
        if (wingFuel <= 36000) { //B-C
            tanks[0] = 4000;
            tanks[9] = 4000;
            tanks[1] = (wingFuel - 8000) / 4;
            tanks[4] = (wingFuel - 8000) / 4;
            tanks[5] = (wingFuel - 8000) / 4;
            tanks[8] = (wingFuel - 8000) / 4;
            return tanks;
        }
        if (wingFuel <= 47000) { //C-D
            tanks[1] = 7000;
            tanks[4] = 7000;
            tanks[5] = 7000;
            tanks[8] = 7000;

            tanks[0] = 4000;
            tanks[9] = 4000;

            tanks[3] = (wingFuel - 36000) / 2;
            tanks[6] = (wingFuel - 36000) / 2;
            return tanks;
        }
        if (wingFuel <= 103788) { //D-E
            double wf = (double) wingFuel;
            tanks[0] = 4000;
            tanks[9] = 4000;
            tanks[3] = 5500;
            tanks[6] = 5500;
            tanks[4] = (int) std::round(0.2612523773*wf - 5278.8617331);
            tanks[5] = (int) std::round(0.2612523773*wf - 5278.8617331);
            tanks[1] = (int) std::round(0.2387476227*wf - 4221.1382669);
            tanks[8] = (int) std::round(0.2387476227*wf - 4221.1382669);
            return tanks;
        }
        if (wingFuel <= 158042) { //E-F
            tanks[0] = 4000;
            tanks[9] = 4000;

            tanks[3] = 5500;
            tanks[6] = 5500;

            tanks[4] = 21836;
            tanks[5] = 21836;

            tanks[1] = 20558;
            tanks[8] = 20558;

            tanks[2] = (wingFuel - 103788) / 2;
            tanks[7] = (wingFuel - 103788) / 2;
            return tanks;
        }
        if (wingFuel <= 215702) { //F-G
            tanks[0] = 4000;
            tanks[9] = 4000;

            tanks[4] = 21836;
            tanks[5] = 21836;

            tanks[1] = 20558;
            tanks[8] = 20558;

            tanks[2] = 27127;
            tanks[7] = 27127;

            tanks[3] = (wingFuel - 147042) / 2;
            tanks[6] = (wingFuel - 147042) / 2;
            return tanks;
        }
        if (wingFuel <= 223088) { //F-G
            tanks[4] = 21836;
            tanks[5] = 21836;

            tanks[1] = 20558;
            tanks[8] = 20558;

            tanks[2] = 27127;
            tanks[7] = 27127;

            tanks[3] = 34330;
            tanks[6] = 34330;

            tanks[0] = (wingFuel - 207702) / 2; //max of 7693
            tanks[9] = (wingFuel - 207702) / 2;
            return tanks;
        }
        else {
            double wf = (double) wingFuel;
            tanks[4] = (int) std::round(0.09786853238*wf + 2.704848682);
            tanks[5] = (int) std::round(0.09786853238*wf + 2.704848682);

            tanks[1] = (int) std::round(0.09217377156*wf - 4.862349496);
            tanks[8] = (int) std::round(0.09217377156*wf - 4.862349496);

            tanks[2] = (int) std::round(0.1216238204*wf - 5.81483892);
            tanks[7] = (int) std::round(0.1216238204*wf - 5.81483892);

            tanks[3] = (int) std::round(0.1539212496*wf - 7.983729255);
            tanks[6] = (int) std::round(0.1539212496*wf - 7.983729255);

            tanks[0] = (int) std::round(0.03449397982*wf - 2.192971038);
            tanks[9] = (int) std::round(0.03449397982*wf - 2.192971038);
            return tanks;
        }
    }

    int* FuelDistributor::totalFuelDistributor(int PFQ, int ZFW, double ZFCQ) {
        int trimFuel = this->distributionTables->calculateTrimFuel(ZFW, PFQ, ZFCQ);

        int wingFuel = PFQ - trimFuel;

        int* tanks = this->wingDistributor(wingFuel);
        tanks[10] = trimFuel;

        return tanks;
    }

    int *FuelDistributor::totalFuelDistributor(int PFQ) {
        int trimFuel = this->distributionTables->calculateTrimFuel(PFQ);

        int wingFuel = PFQ - trimFuel;

        int* tanks = this->wingDistributor(wingFuel);
        tanks[10] = trimFuel;

        return tanks;
    }


}