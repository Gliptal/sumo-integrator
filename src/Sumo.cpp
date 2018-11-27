#include "include/sumo-integrator/Sumo.h"

#include "include/sumo-integrator/Connection.h"
#include "include/sumo-integrator/Ego.h"
#include "include/sumo-integrator/Entities.h"
#include "include/sumo-integrator/Simulation.h"
#include "include/sumo-integrator/debug.h"

#include <lib/sumo/libsumo.h>

#include <string>
#include <vector>


namespace SumoIntegrator {

Sumo::Sumo() {
    connection = std::unique_ptr<Connection>(new Connection(*this));
    ego        = std::unique_ptr<Ego>(new Ego(*this));
    entities   = std::unique_ptr<Entities>(new Entities(*this));
    simulation = std::unique_ptr<Simulation>(new Simulation(*this));
}

Sumo::~Sumo() {
}

}  // namespace SumoIntegrator
