//
// Created by morei on 01/09/2020.
//

#ifndef A380_SYSTEMS_FUELDISTRIBUTOR_H
#define A380_SYSTEMS_FUELDISTRIBUTOR_H

#include "DistributionTables.h"

namespace PlaneFuelSystem {

    class FuelDistributor {
    private:
        DistributionTables* distributionTables;

        int *wingDistributor(int wingFuel);
    public:
        FuelDistributor();
        int * totalFuelDistributor(int PFQ, int ZFW, double ZFCQ);
        int * totalFuelDistributor(int PFQ);
    };

}


#endif //A380_SYSTEMS_FUELDISTRIBUTOR_H
