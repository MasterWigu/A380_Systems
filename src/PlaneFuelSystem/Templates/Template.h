//
// Created by morei on 03/09/2020.
//

#ifndef A380_SYSTEMS_TEMPLATE_H
#define A380_SYSTEMS_TEMPLATE_H

namespace PlaneFuelSystem {

    class Template {
    private:
        bool* pumps;
        bool* tkVls;
        bool* busVls;
    public:
        Template(bool* pp, bool* tv, bool* bv);

        bool* getPumps();
        bool* getTkValves();
        bool* getBusValves();
    };
}


#endif //A380_SYSTEMS_TEMPLATE_H
