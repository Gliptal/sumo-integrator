#include "test/Driver.h"

#include <lib/sumo/libsumo.h>


namespace Test {

Driver::Driver(const double tickrate)
    : tickrate(tickrate) {
}

Driver::~Driver() {
}

Position Driver::get_position() {
    return position;
}

double Driver::get_speed() {
    return speed;
}

void Driver::set_speed(const double speed) {
    this->speed = speed;
}

}  // namespace Test
