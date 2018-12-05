#ifndef TEST_DRIVERS_INPUTDRIVER_H
#define TEST_DRIVERS_INPUTDRIVER_H


#include "test/drivers/Driver.h"


namespace test {

class InputDriver : public Driver {
public:
    InputDriver(const double);
    ~InputDriver();

    void load_network(const double[][3], const size_t);
    void set_spawn(const double, const double, const double);
    void catch_input(const double);
    void tick();

private:
    enum LANE {
        NORTH_RIGHT,
        NORTH_LEFT,
        EAST_RIGHT,
        EAST_LEFT,
        SOUTH_RIGHT,
        SOUTH_LEFT,
        WEST_RIGHT,
        WEST_LEFT
    };

    LANE lane;

    void switch_lane(const bool);
    void drive_straight(const double);
    void follow_turn();
    void follow_lane();
};

}  // namespace test


#endif  // TEST_DRIVERS_INPUTDRIVER_H
