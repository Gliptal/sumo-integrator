#include "config/test/outputbasic.h"

#include <include/Integrator/Sumo.h>
#include <lib/sumo/libsumo.h>

#include <iomanip>
#include <iostream>
#include <vector>


using namespace Integrator;


int main() {
    try {
        bool success;

        Sumo sumo;

        success = sumo.connect(Settings::Network::IP, Settings::Network::PORT);
        if (!success)
            return 1;

        uint steps = Settings::Simulation::END_TIME / Settings::Simulation::TICKRATE;
        for (uint step = 0; step < steps; step++) {
            uint spawnStep = Settings::Traffic::START_TIME / Settings::Simulation::TICKRATE;

            sumo.tick();

            if (step == spawnStep) {
                std::vector<int> request {VAR_POSITION3D, VAR_ANGLE, VAR_SPEED};

                sumo.subscribe(sumo.vehicle, Settings::Traffic::ID, request, Settings::Traffic::START_TIME, Settings::Simulation::END_TIME);

                std::cout << "\n";
            }

            if (step >= spawnStep) {
                libsumo::TraCIResults results = sumo.get_datafeed(sumo.vehicle, Settings::Traffic::ID);

                Position* position          = (Position*) results[VAR_POSITION3D].get();
                libsumo::TraCIDouble* angle = (libsumo::TraCIDouble*) results[VAR_ANGLE].get();
                libsumo::TraCIDouble* speed = (libsumo::TraCIDouble*) results[VAR_SPEED].get();

                std::cout << "\x1b[A\r" << std::flush;
                printf("x = %6.2f (m), y = %6.2f (m), z = %.2f (m) | a = %6.2f (deg) | v = %5.2f (m/s)", position->x, position->y, position->z, angle->value, speed->value);
                std::cout << "\n";
            }
        }

        sumo.close();

        return 0;
    }
    catch (tcpip::SocketException except) {
        return 1;
    }
}
