#include "config/test/egobasic.h"

#include "test/StaticDriver.h"

#include <include/Integrator/Sumo.h>
#include <lib/sumo/libsumo.h>


using namespace Integrator;
using namespace Test;


int main() {
    try {
        bool success;

        StaticDriver ego = StaticDriver(Settings::Simulation::TICKRATE);
        ego.load_network(Settings::Simulation::NETWORK, 4);
        ego.set_spawn(Settings::Ego::SPAWN_POSITION[0], Settings::Ego::SPAWN_POSITION[1], Settings::Ego::SPAWN_POSITION[2]);
        ego.set_speed(Settings::Ego::MAX_SPEED);

        Sumo sumo;

        success = sumo.connect(Settings::Network::IP, Settings::Network::PORT);
        if (!success)
            return 1;

        uint steps = Settings::Simulation::END_TIME / Settings::Simulation::TICKRATE;
        for (uint step = 0; step < steps; step++) {
            ego.tick();
            sumo.move_ego(Settings::Ego::ID, ego.get_position());
            sumo.tick();
        }

        sumo.close();

        return 0;
    }
    catch (tcpip::SocketException except) {
        return 1;
    }
}
