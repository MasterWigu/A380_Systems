//
// Created by morei on 18/10/2020.
//

#ifndef A380_SYSTEMS_COCKPITCONTROLS_H
#define A380_SYSTEMS_COCKPITCONTROLS_H

namespace Cockpit {

    class CockpitControls {
    private:
        int* fuelButtons;
        int* ecamButtons;
    public:
        CockpitControls();

        int* getFuelButtons();
        void setFuelButton(int id, int state);

        int* getEcamButtons();
        void setEcamButton(int id, int state);
    };
}


#endif //A380_SYSTEMS_COCKPITCONTROLS_H
