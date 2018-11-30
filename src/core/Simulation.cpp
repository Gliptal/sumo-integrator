#include "include/sumo-integrator/core/Simulation.h"

#include "include/sumo-integrator/utils/debug.h"

#include <lib/sumo/libsumo.h>


namespace sumointegrator {

Sumo::Simulation::Simulation(TraCIAPI& api)
    : Concern(api) {
}

Sumo::Simulation::~Simulation() {
}

void Sumo::Simulation::tick() {
    api.simulationStep();

    LOG_DATA("tick")
}

void Sumo::Simulation::tick(const double time) {
    api.simulationStep(time);

    LOG_DATA("tick");
}

}  // namespace sumointegrator
