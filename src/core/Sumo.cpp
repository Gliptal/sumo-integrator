#include "include/sumo-integrator/core/Sumo.h"

#include "include/sumo-integrator/core/Connection.h"
#include "include/sumo-integrator/core/Ego.h"
#include "include/sumo-integrator/core/Entities.h"
#include "include/sumo-integrator/core/Simulation.h"
#include "include/sumo-integrator/utils/debug.h"

#include <memory>


namespace sumointegrator {

Sumo::Sumo() {
    connection = std::unique_ptr<Connection>(new Connection(*this));
    ego        = std::unique_ptr<Ego>(new Ego(*this));
    entities   = std::unique_ptr<Entities>(new Entities(*this));
    simulation = std::unique_ptr<Simulation>(new Simulation(*this));
}

Sumo::~Sumo() {
}

}  // namespace sumointegrator
