//
// Created by morei on 31/08/2020.
//

#ifndef A380_SYSTEMS_DISTRIBUTIONTABLES_H
#define A380_SYSTEMS_DISTRIBUTIONTABLES_H

namespace PlaneFuelSystem {
    class DistributionTables {
    private:
        int* ZFWs;
        int* PFQ;
        int*** trimFuel;

    public:
        DistributionTables();
    };
}

#endif //A380_SYSTEMS_DISTRIBUTIONTABLES_H
