//
// Created by morei on 08/09/2020.
//

#ifndef A380_SYSTEMS_INNERFEEDS_H
#define A380_SYSTEMS_INNERFEEDS_H


namespace PlaneFuelSystem {
    class InnerFeeds {
    private:
        bool* valveStates;
        bool* pumpStates;
        bool ** output;
    public:
        InnerFeeds();
        ~InnerFeeds();

        bool **getTemplate(const int *tanks, int *pmpFailures, int *vlvFailures, const bool *cases, bool aut);
    };
}


#endif //A380_SYSTEMS_INNERFEEDS_H
