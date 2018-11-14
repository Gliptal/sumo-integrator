#ifndef TEST_STATICDRIVER_H
#define TEST_STATICDRIVER_H


#include "test/Driver.h"

#include <lib/sumo/libsumo.h>


namespace Test {

class StaticDriver : public Driver {
public:
    StaticDriver(const double);
    ~StaticDriver();

    void load_network(const double[][3], const size_t);
    void set_spawn(const double, const double, const double);
    void tick();
};

}  // namespace Test


#endif  // TEST_STATICDRIVER_H
