#include "include/sumo-integrator/Ego.h"

#include "include/sumo-integrator/debug.h"

#include <lib/sumo/libsumo.h>

#include <stdexcept>
#include <string>


namespace SumoIntegrator {

Sumo::Ego::Ego(TraCIAPI& api)
    : Concern(api) {
}

Sumo::Ego::~Ego() {
}

void Sumo::Ego::move(const Position& position) {
    if (id.empty())
        throw libsumo::TraCIException("id not set");

    move(id, position);
}

void Sumo::Ego::move(const std::string& id, const Position& position) {
    api.vehicle.moveToXY(id, "", 0, position.x, position.y, -1073741824, 2);
}

std::string Sumo::Ego::get_id() {
    return id;
}

void Sumo::Ego::set_id(const std::string& id) {
    this->id = id;
}

}  // namespace SumoIntegrator
