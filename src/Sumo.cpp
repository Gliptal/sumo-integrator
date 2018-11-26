#include "include/sumo-integrator/Sumo.h"

#include "include/sumo-integrator/Connection.h"
#include "include/sumo-integrator/Ego.h"
#include "include/sumo-integrator/debug.h"

#include <lib/sumo/libsumo.h>

#include <string>
#include <vector>


namespace SumoIntegrator {

Sumo::Sumo() {
    connection = std::unique_ptr<Connection>(new Connection(*this));
    ego        = std::unique_ptr<Ego>(new Ego(*this));
}

Sumo::~Sumo() {
}

void Sumo::tick() {
    simulationStep();

    LOG_DATA("tick")
}

void Sumo::tick(const double time) {
    simulationStep(time);

    LOG_DATA("tick");
}

void Sumo::subscribe(TraCIAPI::TraCIScopeWrapper& entity, const std::string& id, const std::vector<int>& request, const double start, const double end) {
    entity.subscribe(id, request, start, end);

    LOG_INFO_SUCCESS("subscribed to %s", id.c_str());
}

libsumo::TraCIResults Sumo::get_datafeed(TraCIAPI::TraCIScopeWrapper& entity, const std::string& id) {
    libsumo::TraCIResults datafeed = entity.getSubscriptionResults(id);

    LOG_DATA("received %d data", datafeed.size());

    return datafeed;
}

void Sumo::move_ego(const std::string& id, const Position& position) {
    vehicle.moveToXY(id, "", 0, position.x, position.y, -1073741824, 2);
}

}  // namespace SumoIntegrator
