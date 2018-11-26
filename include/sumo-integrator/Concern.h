#ifndef INCLUDE_SUMOINTEGRATOR_CONCERN_H
#define INCLUDE_SUMOINTEGRATOR_CONCERN_H


#include "include/sumo-integrator/Sumo.h"


namespace SumoIntegrator {

class Sumo::Concern {
public:
    Concern(TraCIAPI& api);
    ~Concern();

protected:
    TraCIAPI& api;
};

}  // namespace SumoIntegrator


#endif  // INCLUDE_SUMOINTEGRATOR_CONCERN_H
