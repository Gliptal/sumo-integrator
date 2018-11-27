#include "include/sumo-integrator/Simulation.h"

#include "include/sumo-integrator/debug.h"

#include <lib/sumo/libsumo.h>


namespace SumoIntegrator {

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

}  // namespace SumoIntegrator
