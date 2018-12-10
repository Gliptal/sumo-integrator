#include "config/test/outputmultiple.h"

#include <include/sumo-integrator/master.h>

#include <vector>


using namespace sumointegrator;


int main() {
    try {
        std::vector<std::string> subscribed;

        Sumo sumo;
        sumo.connection->open(Settings::Network::IP, Settings::Network::PORT);

        uint steps = Settings::Simulation::END_TIME / Settings::Simulation::TICKRATE;
        for (uint step = 0; step < steps; step++) {
            sumo.simulation->tick();

            std::vector<std::string> spawning = sumo.entities->list_spawning(true, "traffic");
            for (auto i = spawning.begin(); i != spawning.end(); i++) {
                std::vector<int> request {VAR_POSITION3D, VAR_ANGLE, VAR_SPEED};
                sumo.entities->subscribe(sumo.vehicle, *i, request, 0, Settings::Simulation::END_TIME);
                subscribed.push_back(*i);

                std::cout << "\n";
            }

            for (auto i = subscribed.rbegin(); i != subscribed.rend(); i++) {
                types::Datamap results = sumo.entities->poll(sumo.vehicle, *i);

                types::Position* position = (types::Position*) results[VAR_POSITION3D].get();
                double angle              = types::cast_double(results[VAR_ANGLE]);
                double speed              = types::cast_double(results[VAR_SPEED]);

                for (uint j = 0; j < (i - subscribed.rbegin() + 1) * 2 - 1; j++)
                    std::cout << "\x1b[A\r" << std::flush;
                printf("x = %6.2f (m), y = %6.2f (m), z = %.2f (m) | a = %6.2f (deg) | v = %5.2f (m/s)", position->x, position->y, position->z, angle, speed);
                for (uint j = 0; j < (i - subscribed.rbegin() + 1) * 2 - 1; j++)
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
