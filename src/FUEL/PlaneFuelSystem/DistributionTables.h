//
// Created by MasterWigu on 31/08/2020.
//

#ifndef A380_SYSTEMS_DISTRIBUTIONTABLES_H
#define A380_SYSTEMS_DISTRIBUTIONTABLES_H

namespace PlaneFuelSystem {

    /// This class calculates the fuel in the trim tank by using the tables from the WBM
    class DistributionTables {
    private:
        int*** trimFuel;

        static int calculateWeightIndex(int ZFW);
        static int calculateZFCGClass(double CG);
        static int calculatePFQClass(int PFQ);
    public:
        DistributionTables();
        int calculateTrimFuel(int ZFW, int cPFQ, double ZFCG);
        int calculateTrimFuel(int cPFQ);
    };
}

#endif //A380_SYSTEMS_DISTRIBUTIONTABLES_H
