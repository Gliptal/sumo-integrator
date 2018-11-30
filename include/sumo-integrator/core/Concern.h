#ifndef INCLUDE_SUMOINTEGRATOR_CORE_CONCERN_H
#define INCLUDE_SUMOINTEGRATOR_CORE_CONCERN_H


#include "include/sumo-integrator/core/Sumo.h"


namespace sumointegrator {

class Sumo::Concern {
public:
    Concern(TraCIAPI& api);
    ~Concern();

protected:
    TraCIAPI& api;
};

}  // namespace sumointegrator


#endif  // INCLUDE_SUMOINTEGRATOR_CORE_CONCERN_H
