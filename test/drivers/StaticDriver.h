#ifndef TEST_DRIVERS_STATICDRIVER_H
#define TEST_DRIVERS_STATICDRIVER_H


#include "test/drivers/Driver.h"


namespace test {

class StaticDriver : public Driver {
public:
    StaticDriver(const double);
    ~StaticDriver();

    void load_network(const double[][3], const size_t);
    void set_spawn(const double, const double, const double);
    void vary_speed(const double, const double, const double, const double);
    void tick();
};

}  // namespace test


#endif  // TEST_DRIVERS_STATICDRIVER_H
