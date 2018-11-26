#include "config/test/egobasic.h"

#include "test/StaticDriver.h"

#include <include/sumo-integrator/Connection.h>
#include <include/sumo-integrator/Sumo.h>
#include <lib/sumo/libsumo.h>


using namespace SumoIntegrator;
using namespace Test;


int main() {
    try {
        StaticDriver ego = StaticDriver(Settings::Simulation::TICKRATE);
        ego.load_network(Settings::Simulation::NETWORK, 4);
        ego.set_spawn(Settings::Ego::SPAWN_POSITION[0], Settings::Ego::SPAWN_POSITION[1], Settings::Ego::SPAWN_POSITION[2]);
        ego.set_speed(Settings::Ego::MAX_SPEED / 2);

        Sumo sumo;
        sumo.connection->open(Settings::Network::IP, Settings::Network::PORT);

        std::cout << "\n";

        uint steps = Settings::Simulation::END_TIME / Settings::Simulation::TICKRATE;
        for (uint step = 0; step < steps; step++) {
            ego.vary_speed(0.001, Settings::Ego::MIN_SPEED, Settings::Ego::MAX_SPEED, 3.0);

            std::cout << "\x1b[A\r" << std::flush;
            printf("v = %5.2f (m/s)", ego.get_speed());
            std::cout << "\n";

            ego.tick();
            sumo.move_ego(Settings::Ego::ID, ego.get_position());
            sumo.tick();
        }

        sumo.connection->close();

        return 0;
    }
    catch (...) {
        return 1;
    }
}
