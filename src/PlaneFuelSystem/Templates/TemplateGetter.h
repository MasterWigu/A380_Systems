//
// Created by morei on 03/09/2020.
//

#ifndef A380_SYSTEMS_TEMPLATEGETTER_H
#define A380_SYSTEMS_TEMPLATEGETTER_H

#include "Template.h"

namespace PlaneFuelSystem {
    class TemplateGetter {
    private:
        PlaneFuelSystem::Template** templates;

    public:
        TemplateGetter();

        Template* getTemplate(int id);

    };

}


#endif //A380_SYSTEMS_TEMPLATEGETTER_H
