#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H


#include <lib/sumo/libsumo.h>

#include <array>
#include <vector>


namespace Test {

class Driver {
    typedef std::vector<std::array<double, 3>> Network;

public:
    virtual ~Driver();

    Position get_position();
    double get_speed();
    void set_speed(const double);

protected:
    double tickrate;
    Network network;
    Position position;
    double speed;

    Driver(const double);

    virtual void load_network(const double[][3], const size_t)       = 0;
    virtual void set_spawn(const double, const double, const double) = 0;
    virtual void tick()                                              = 0;
};

}  // namespace Test


#endif  // TEST_DRIVER_H
