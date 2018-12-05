#include <string>


namespace Settings {

namespace Network {

const std::string IP = "127.0.0.1";
const uint PORT      = 6666;

}  // namespace Network

namespace Simulation {

// clang-format off
const double NETWORK[8][3] = {
    {-195.20,  95.20, 0.00}, {-195.20,  98.40, 0.00},
    {-104.80,  95.20, 0.00}, {-101.60,  95.20, 0.00},
    {-104.80, -95.20, 0.00}, {-104.80, -98.40, 0.00},
    {-195.20, -95.20, 0.00}, {-198.40, -95.20, 0.00}
};
// clang-format on

const double TICKRATE = 0.100;
const double END_TIME = 120;

}  // namespace Simulation

namespace Ego {

const double SPAWN_POSITION[3] = {-191.67, 95.20, 0.00};
const std::string ID           = "EGO";

const double SPEED_DELTA = 1;

}  // namespace Ego

}  // namespace Settings
