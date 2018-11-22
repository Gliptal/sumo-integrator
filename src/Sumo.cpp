#include "include/Integrator/Sumo.h"
#include "include/Integrator/debug.h"

#include <lib/sumo/libsumo.h>

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


namespace Integrator {

Sumo::Sumo() {
}

Sumo::~Sumo() {
}

void Sumo::connect(const std::string& ip, const uint port) {
    try {
        TraCIAPI::connect(ip, port);

        LOG_INFO_SUCCESS("connected to %s:%d", ip.c_str(), port);
    }
    catch (tcpip::SocketException except) {
        LOG_INFO_FAIL("connecting to %s:%d", ip.c_str(), port);

        throw;
    }
}

void Sumo::close() {
    TraCIAPI::close();

    LOG_INFO_SUCCESS("connection closed");
}

void Sumo::tick() {
    simulationStep();

    LOG_DATA("tick")
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

}  // namespace Integrator
