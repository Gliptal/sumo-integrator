#include "test/drivers/FreeDriver.h"

#include <cmath>
#include <curses.h>


namespace test {

FreeDriver::FreeDriver(const double tickrate, const double accel, const double decel, const double angl)
    : Driver(tickrate),
      accel(accel),
      decel(decel),
      angl(angl) {
}

FreeDriver::~FreeDriver() {
}

void FreeDriver::load_network(const double network[][3], const size_t nodes) {
    for (size_t i = 0; i < nodes; i++)
        this->network.push_back({network[i][0], network[i][1], network[i][2]});
}

void FreeDriver::set_spawn(const double x, const double y, const double z) {
    position.x = x;
    position.y = y;
    position.z = z;
}

void FreeDriver::set_spawn(const double x, const double y, const double z, const double a) {
    set_spawn(x, y, z);

    yaw = a;
}

void FreeDriver::catch_input() {
    initscr();
    halfdelay(tickrate > 0.1 ? tickrate * 10 : 1);
    noecho();

    switch (getch()) {
        case 'w':
            speed += (speed >= 0 ? accel * tickrate : decel * tickrate);
            break;
        case 's':
            speed -= decel * tickrate;
            break;
        case 'a':
            yaw -= (speed > 2 ? angl * tickrate : angl * 4 * tickrate);
            break;
        case 'd':
            yaw += (speed > 2 ? angl * tickrate : angl * 4 * tickrate);
            break;
        default:
            break;
    }

    endwin();
}

void FreeDriver::tick() {
    position.x += std::sin(yaw) * (speed * tickrate);
    position.y += std::cos(yaw) * (speed * tickrate);
}

double FreeDriver::get_yaw() {
    return yaw;
}


}  // namespace test
