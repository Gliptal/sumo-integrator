#include "config/test/egofree.h"

#include "test/drivers/FreeDriver.h"

#include <include/sumo-integrator/master.h>


using namespace sumointegrator;
using namespace test;


int main() {
    try {
        FreeDriver ego = FreeDriver(Settings::Simulation::TICKRATE, Settings::Ego::ACCEL, Settings::Ego::DECEL, Settings::Ego::ANGULAR);
        ego.set_spawn(Settings::Ego::SPAWN_POSITION[0], Settings::Ego::SPAWN_POSITION[1], Settings::Ego::SPAWN_POSITION[2], Settings::Ego::SPAWN_POSITION[3]);

        Sumo sumo;
        sumo.connection->open(Settings::Network::IP, Settings::Network::PORT);
        sumo.ego->set_id(Settings::Ego::ID);

        std::cout << "\n";

        uint steps = Settings::Simulation::END_TIME / Settings::Simulation::TICKRATE;
        for (uint step = 0; step < steps; step++) {
            ego.catch_input();

            ego.tick();
            sumo.ego->move(ego.get_position(), ego.get_yaw());
            sumo.simulation->tick();

            std::cout << "\x1b[A\r" << std::flush;
            printf("v = %6.2f (m/s)", ego.get_speed());
            std::cout << "\n";
        }

        sumo.connection->close();

        return 0;
    }
    catch (...) {
        return 1;
    }
}
