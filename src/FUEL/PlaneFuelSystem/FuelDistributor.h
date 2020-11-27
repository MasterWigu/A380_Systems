#ifndef A380_SYSTEMS_FUELDISTRIBUTOR_H
#define A380_SYSTEMS_FUELDISTRIBUTOR_H

#include "DistributionTables.h"

namespace PlaneFuelSystem {

    /// @class Fuel Distributor is responsible for calculating the fuel in each tank when the plane is refueled according to the WBM and FCOM
    /// It uses the @class DistributionTables to calculate fuel in the trim tank
    class FuelDistributor {
    private:
        DistributionTables* distributionTables;

        int *wingDistributor(int wingFuel);
    public:

        /// Instantiates a new fuel distributor
        FuelDistributor();

        /// Distributes the fuel between all the aircraft's tanks
        /// @param [in] PFQ - Preselected Fuel Quantity (kg)
        /// @param [in] ZFW - Zero fuel weight of the aircraft (kg)
        /// @param [in] ZFCG - Zero Fuel Center of Gravity (%RC)
        /// @return persistent pointer to array of ints with 11 elements, which correspond to the fuel in each of the 11 tanks (position in array = tank id)
        int * totalFuelDistributor(int PFQ, int ZFW, double ZFCQ);

        /// Distributes the fuel between all the aircraft's tanks, assuming ZFW = 300 000 kg and ZFCG = 36.5 %RC
        /// @param [in] PFQ - Preselected Fuel Quantity (kg)
        /// @return persistent pointer to array of ints with 11 elements, which correspond to the fuel in each of the 11 tanks (position in array = tank id)
        int * totalFuelDistributor(int PFQ);
    };

}


#endif //A380_SYSTEMS_FUELDISTRIBUTOR_H
