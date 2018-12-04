#include "config/test/egoasync.h"

#include "test/drivers/StaticDriver.h"

#include <include/sumo-integrator/master.h>

#include <ctime>


#define NANO_SEC 1000000000L


using namespace sumointegrator;
using namespace test;


int main() {
    try {
        StaticDriver ego = StaticDriver(Settings::Simulation::TICKRATE);
        ego.load_network(Settings::Simulation::NETWORK, 4);
        ego.set_spawn(Settings::Ego::SPAWN_POSITION[0], Settings::Ego::SPAWN_POSITION[1], Settings::Ego::SPAWN_POSITION[2]);
        ego.set_speed(Settings::Ego::MAX_SPEED / 2);

        Sumo sumo;
        sumo.connection->open(Settings::Network::IP, Settings::Network::PORT);
        sumo.ego->set_id(Settings::Ego::ID);

        std::cout << "\n";

        double time = 0;
        while (time <= Settings::Simulation::END_TIME) {
            ego.tick();
            sumo.ego->move(ego.get_position());
            sumo.simulation->tick(time);

            {
                timespec target;
                timespec remain;

                target.tv_sec  = 0;
                target.tv_nsec = Settings::Simulation::TICKRATE * NANO_SEC;

                int result;
                result = nanosleep(&target, &remain);

                if (result == 0)
                    time += Settings::Simulation::TICKRATE;
                else
                    time += (target.tv_nsec - remain.tv_nsec) / NANO_SEC;
            }

            std::cout << "\x1b[A\r" << std::flush;
            printf("t = %5.2f (s)", time);
            std::cout << "\n";
        }

        sumo.connection->close();

        return 0;
    }
    catch (...) {
        return 1;
    }
}
