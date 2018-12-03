#include "include/sumo-integrator/core/Ego.h"

#include "include/sumo-integrator/utils/debug.h"

#include <lib/sumo/libsumo.h>

#include <string>


namespace sumointegrator {

Sumo::Ego::Ego(TraCIAPI& api)
    : Concern(api) {
}

Sumo::Ego::~Ego() {
}

void Sumo::Ego::subscribe(const std::vector<int>& request, const double radius, const double start, const double end) {
    api.vehicle.subscribeContext(id, CMD_GET_VEHICLE_VARIABLE, radius, request, start, end);

    LOG_INFO_SUCCESS("subscribed to %s's %.2f (m) context", id.c_str(), radius);
}

libsumo::SubscriptionResults Sumo::Ego::poll() {
    libsumo::SubscriptionResults data = api.vehicle.getContextSubscriptionResults(id);

    LOG_DATA("received %d data", data.size());

    return data;
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

}  // namespace sumointegrator
