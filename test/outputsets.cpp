#include "config/test/outputsets.h"

#include <include/sumo-integrator/master.h>

#include <bitset>


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
            if (subscribed.empty() && !spawning.empty()) {
                sumo.entities->subscribe(sumo.vehicle, spawning[0], sumo.entities->DATASETS["TRANSFORM"], 0, Settings::Simulation::END_TIME);
                sumo.entities->subscribe(sumo.vehicle, spawning[0], sumo.entities->DATASETS["VECTORS"], 0, Settings::Simulation::END_TIME);
                sumo.entities->subscribe(sumo.vehicle, spawning[0], sumo.entities->DATASETS["STATE"], 0, Settings::Simulation::END_TIME);
                subscribed.push_back(spawning[0]);

                std::cout << "\n";
            }

            if (!subscribed.empty()) {
                types::Datamap results = sumo.entities->poll(sumo.vehicle, subscribed[0]);

                types::Position* position = (types::Position*) results[VAR_POSITION3D].get();
                double angle              = types::cast_double(results[VAR_ANGLE]);

                double speed        = types::cast_double(results[VAR_SPEED]);
                double acceleration = types::cast_double(results[VAR_ACCELERATION]);

                std::bitset<16> lights = types::cast_int(results[VAR_SIGNALS]);
                std::bitset<16> state  = types::cast_int(results[VAR_STOPSTATE]);

                std::cout << "\x1b[A\r"
                          << "\x1b[A\r"
                          << "\x1b[A\r" << std::flush;
                printf("x = %6.2f (m), y = %6.2f (m), z = %.2f (m) | a = %6.2f (deg)", position->x, position->y, position->z, angle);
                std::cout << "\n";
                printf("v = %5.2f (m/s) | a = %5.2f (m/s2)", speed, acceleration);
                std::cout << "\n";
                printf("blinker = %d, brakes = %d | stopped = %d", lights[0] || lights[1], (int) lights[3], (int) state[0]);
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
