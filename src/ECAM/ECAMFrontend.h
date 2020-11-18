//
// Created by MasterWigu on 07/11/2020.
//

#ifndef A380_SYSTEMS_ECAMFRONTEND_H
#define A380_SYSTEMS_ECAMFRONTEND_H

#include <cstdlib>

namespace ECAM {
    class ECAMFrontend {
        //*************************** GENERAL ***************************
    private:
        int SDShownId;
    public:
        ECAMFrontend();

        int getSdShownId() const;
        void setSdShownId(int sdShownId);


        //*************************** FUEL ***************************
    private:
        int* tankQuantities;
        int* pmpStates;
        int* vlvStates;

    public:
        void getTankQuantities(int *out);
        void setTankQuantities(int *tankQuantities);

        void getPmpStates(int *out);
        void setPmpStates(int *pmpStates);

    };
}


#endif //A380_SYSTEMS_ECAMFRONTEND_H
