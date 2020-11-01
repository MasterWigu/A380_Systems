//
// Created by morei on 17/10/2020.
//

#ifndef A380_SYSTEMS_FUELSYSTEMFRONTEND_H
#define A380_SYSTEMS_FUELSYSTEMFRONTEND_H

namespace FuelSystem {
    class FuelSystemFrontend {
    private:
        double* tankLevels;
    public:
        double* getTankLevels();
        void setTankLevels(double* levels);
    };
}


#endif //A380_SYSTEMS_FUELSYSTEMFRONTEND_H
