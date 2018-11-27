#include "test/StaticDriver.h"

#include <cstdlib>
#include <vector>


namespace Test {

StaticDriver::StaticDriver(const double tickrate)
    : Driver(tickrate) {
}

StaticDriver::~StaticDriver() {
}

void StaticDriver::load_network(const double network[][3], const size_t nodes) {
    for (size_t i = 0; i < nodes; i++)
        this->network.push_back({network[i][0], network[i][1], network[i][2]});
}

void StaticDriver::set_spawn(const double x, const double y, const double z) {
    position.x = x;
    position.y = y;
    position.z = z;
}

void StaticDriver::vary_speed(const double rate, const double min, const double max, const double var) {
    double random = ((double) rand()) / RAND_MAX;

    if (random <= rate) {
        double delta;
        do {
            delta = -var + (((double) rand()) / RAND_MAX * (var + var));
        } while (speed + delta < min || speed + delta > max);

        speed += delta;
    }
}

void StaticDriver::tick() {
    double spacerate = speed * tickrate;

    // north lane
    if (position.y >= network[0][1] - 0.01) {
        position.y = network[0][1];
        position.x += spacerate;
    }
    // east lane
    if (position.x >= network[1][0] - 0.01) {
        position.x = network[1][0];
        position.y -= spacerate;
    }
    // south lane
    if (position.y <= network[2][1] + 0.01) {
        position.y = network[2][1];
        position.x -= spacerate;
    }
    // west lane
    if (position.x <= network[3][0] + 0.01) {
        position.x = network[3][0];
        position.y += spacerate;
    }
}

}  // namespace Test
