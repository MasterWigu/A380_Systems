//
// Created by morei on 01/11/2020.
//

#ifndef A380_SYSTEMS_SIMULATORDATA_H
#define A380_SYSTEMS_SIMULATORDATA_H

namespace PluginControl {
    class SimulatorData {
    private:
        float simulatorTime;
        int planeGW;
        double planeCurrCG;
        int FL;

    public:
        float getSimulatorTime() const;

        void setSimulatorTime(float simulatorTime);

        int getPlaneGw() const;

        void setPlaneGw(int planeGw);

        double getPlaneCurrCg() const;

        void setPlaneCurrCg(double planeCurrCg);

        int getFl() const;

        void setFl(int fl);

    };
}


#endif //A380_SYSTEMS_SIMULATORDATA_H
