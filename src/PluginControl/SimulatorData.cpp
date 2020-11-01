//
// Created by morei on 01/11/2020.
//

#include "SimulatorData.h"

namespace PluginControl {

    float SimulatorData::getSimulatorTime() const {
        return simulatorTime;
    }

    void SimulatorData::setSimulatorTime(float sT) {
        simulatorTime = sT;
    }

    int SimulatorData::getPlaneGw() const {
        return planeGW;
    }

    void SimulatorData::setPlaneGw(int planeGw) {
        planeGW = planeGw;
    }

    double SimulatorData::getPlaneCurrCg() const {
        return planeCurrCG;
    }

    void SimulatorData::setPlaneCurrCg(double planeCurrCg) {
        planeCurrCG = planeCurrCg;
    }

    int SimulatorData::getFl() const {
        return FL;
    }

    void SimulatorData::setFl(int fl) {
        FL = fl;
    }
}