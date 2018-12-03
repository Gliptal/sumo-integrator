#include "config/test/egosubscribe.h"

#include "test/drivers/StaticDriver.h"

#include <include/sumo-integrator/master.h>
#include <lib/sumo/libsumo.h>


using namespace sumointegrator;
using namespace test;


int main() {
    try {
        StaticDriver ego = StaticDriver(Settings::Simulation::TICKRATE);
        ego.load_network(Settings::Simulation::NETWORK, 4);
        ego.set_spawn(Settings::Ego::SPAWN_POSITION[0], Settings::Ego::SPAWN_POSITION[1], Settings::Ego::SPAWN_POSITION[2]);
        ego.set_speed(Settings::Ego::SPEED);

        Sumo sumo;
        sumo.connection->open(Settings::Network::IP, Settings::Network::PORT);
        sumo.ego->set_id(Settings::Ego::ID);
        sumo.ego->subscribe(sumo.entities->DATASETS["TRANSFORM"], Settings::Ego::RADIUS, 0, Settings::Simulation::END_TIME);

        std::cout << "\n";

        uint steps = Settings::Simulation::END_TIME / Settings::Simulation::TICKRATE;
        for (uint step = 0; step < steps; step++) {
            ego.tick();
            sumo.ego->move(ego.get_position());
            sumo.simulation->tick();

            std::cout << "\x1b[A\r" << std::flush;
            printf("n = %d", (int) sumo.ego->poll().size() - 1);
            std::cout << "\n";
        }

        sumo.connection->close();

        return 0;
    }
    catch (...) {
        return 1;
    }
}
