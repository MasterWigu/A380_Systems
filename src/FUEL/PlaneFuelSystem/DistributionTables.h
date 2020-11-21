//
// Created by MasterWigu on 31/08/2020.
//

#ifndef A380_SYSTEMS_DISTRIBUTIONTABLES_H
#define A380_SYSTEMS_DISTRIBUTIONTABLES_H

namespace PlaneFuelSystem {

    /// This class calculates the fuel in the trim tank by using the tables from the WBM.
    class DistributionTables {
    private:
        int*** trimFuel;

        static int calculateWeightIndex(int ZFW);
        static int calculateZFCGClass(double CG);
        static int calculatePFQClass(int PFQ);
    public:

        /// Instantiates the tables
        DistributionTables();

        /// Calculates the fuel (kg) in the trim tank.
        /// @param [in] ZFW - Zero fuel weight of the aircraft (kg)
        /// @param [in] cPFQ - Preselected Fuel Quantity (kg)
        /// @param [in] ZFCG - Zero Fuel Center of Gravity (%RC)
        /// @return the trim tank fuel (kg)
        int calculateTrimFuel(int ZFW, int cPFQ, double ZFCG);

        /// Calculates the fuel (kg) in the trim tank assuming ZFW = 300 000 kg and ZFCG = 36.5 %RC
        /// @param [in] cPFQ - Preselected Fuel Quantity (kg)
        /// @return the trim tank fuel (kg)
        int calculateTrimFuel(int cPFQ);
    };
}

#endif //A380_SYSTEMS_DISTRIBUTIONTABLES_H
