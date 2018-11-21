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

bool Sumo::connect(const std::string& ip, const uint port) {
    try {
        TraCIAPI::connect(ip, port);

#if DEBUG_LEVEL >= DEBUG_INFO
        std::cout << std::left << std::setw(12) << "[ CONN ]" << std::setw(12) << "[  OK  ]"
                  << "connected to " << ip << ":" << port << std::endl;
#endif

        return true;
    }
    catch (tcpip::SocketException except) {
#if DEBUG_LEVEL >= DEBUG_INFO
        std::cout << std::left << std::setw(12) << "[ CONN ]" << std::setw(12) << "[ FAIL ]"
                  << "connecting to " << ip << ":" << port << std::endl;
#endif

        return false;
    }
}

void Sumo::close() {
    TraCIAPI::close();

#if DEBUG_LEVEL >= DEBUG_INFO
    std::cout << std::left << std::setw(12) << "[ CONN ]" << std::setw(12) << "[  OK  ]"
              << "closed" << std::endl;
#endif
}

void Sumo::tick() {
    simulationStep();

#if DEBUG_LEVEL >= DEBUG_ALL
    std::cout << std::left << std::setw(12) << "[ TICK ]" << std::setw(12) << "[  OK  ]" << std::endl;
#endif
}

void Sumo::subscribe(TraCIAPI::TraCIScopeWrapper& entity, const std::string& id, const std::vector<int>& request, const double start, const double end) {
    entity.subscribe(id, request, start, end);
}

libsumo::TraCIResults Sumo::get_datafeed(TraCIAPI::TraCIScopeWrapper& entity, const std::string& id) {
    return entity.getSubscriptionResults(id);
}

void Sumo::move_ego(const std::string& id, const Position& position) {
    vehicle.moveToXY(id, "", 0, position.x, position.y, -1073741824, 2);
}

}  // namespace Integrator
