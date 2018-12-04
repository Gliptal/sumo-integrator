#include "test/drivers/Driver.h"

#include <include/sumo-integrator/types/compound.h>


namespace test {

Driver::Driver(const double tickrate)
    : tickrate(tickrate) {
}

Driver::~Driver() {
}

sumointegrator::types::Position Driver::get_position() {
    return position;
}

double Driver::get_speed() {
    return speed;
}

void Driver::set_speed(const double speed) {
    this->speed = speed;
}

}  // namespace test
