//
// Created by morei on 05/09/2020.
//

#ifndef A380_SYSTEMS_MIDFEED23_H
#define A380_SYSTEMS_MIDFEED23_H

namespace PlaneFuelSystem {
    class MidFeed23 {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        MidFeed23();
        ~MidFeed23();

        bool **getTemplate(const int *tanks, bool *pmpFailures, bool *vlvFailures, const bool *cases, bool aut);
    };
}



#endif //A380_SYSTEMS_MIDFEED23_H
