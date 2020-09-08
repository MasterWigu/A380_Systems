//
// Created by morei on 05/09/2020.
//

#ifndef A380_SYSTEMS_OUTFEEDS_H
#define A380_SYSTEMS_OUTFEEDS_H

namespace PlaneFuelSystem {
    class OutFeeds {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        OutFeeds();
        ~OutFeeds();

        bool **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut, bool someManual);
    };
}



#endif //A380_SYSTEMS_OUTFEEDS_H
