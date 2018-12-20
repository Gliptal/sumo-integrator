#ifndef TEST_DRIVERS_FREEDRIVER_H
#define TEST_DRIVERS_FREEDRIVER_H


#include "test/drivers/Driver.h"


namespace test {

class FreeDriver : public Driver {
public:
    FreeDriver(const double, const double, const double, const double);
    ~FreeDriver();

    void load_network(const double[][3], const size_t);
    void set_spawn(const double, const double, const double);
    void set_spawn(const double, const double, const double, const double);
    void catch_input();
    void tick();

    double get_yaw();

private:
    double accel;
    double decel;
    double angl;

    double yaw;
};

}  // namespace test


#endif  // TEST_DRIVERS_FREEDRIVER_H
