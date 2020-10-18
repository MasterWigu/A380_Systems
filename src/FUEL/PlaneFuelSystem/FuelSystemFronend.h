//
// Created by morei on 17/10/2020.
//

#ifndef A380_SYSTEMS_FUELSYSTEMFRONEND_H
#define A380_SYSTEMS_FUELSYSTEMFRONEND_H

namespace PlaneFuelSystem {
    class FuelSystemFronend {
    private:
        double* tankLevels;
    public:
        double* getTankLevels();
        void setTankLevels(double* levels);
    };
}


#endif //A380_SYSTEMS_FUELSYSTEMFRONEND_H
