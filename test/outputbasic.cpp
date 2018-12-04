#include "config/test/outputbasic.h"

#include <include/sumo-integrator/master.h>

#include <vector>


using namespace sumointegrator;


int main() {
    try {
        Sumo sumo;
        sumo.connection->open(Settings::Network::IP, Settings::Network::PORT);

        uint steps = Settings::Simulation::END_TIME / Settings::Simulation::TICKRATE;
        for (uint step = 0; step < steps; step++) {
            uint spawnStep = Settings::Traffic::START_TIME / Settings::Simulation::TICKRATE;

            sumo.simulation->tick();

            if (step == spawnStep) {
                std::vector<int> request {VAR_POSITION3D, VAR_ANGLE, VAR_SPEED};

                sumo.entities->subscribe(sumo.vehicle, Settings::Traffic::ID, request, Settings::Traffic::START_TIME, Settings::Simulation::END_TIME);

                std::cout << "\n";
            }

            if (step >= spawnStep) {
                types::Datamap results = sumo.entities->poll(sumo.vehicle, Settings::Traffic::ID);

                types::Position* position = (types::Position*) results[VAR_POSITION3D].get();
                double angle              = types::cast_double(results[VAR_ANGLE]);
                double speed              = types::cast_double(results[VAR_SPEED]);

                std::cout << "\x1b[A\r" << std::flush;
                printf("x = %6.2f (m), y = %6.2f (m), z = %.2f (m) | a = %6.2f (deg) | v = %5.2f (m/s)", position->x, position->y, position->z, angle, speed);
                std::cout << "\n";
            }
        }

        sumo.connection->close();

        return 0;
    }
    catch (...) {
        return 1;
    }
}
