#include <string>


namespace Settings {

namespace Network {

const std::string IP = "127.0.0.1";
const uint PORT      = 6666;

}  // namespace Network

namespace Simulation {

const double TICKRATE = 0.100;
const double END_TIME = 120;

}  // namespace Simulation

namespace Ego {

const double SPAWN_POSITION[4] = {-191.67, 95.20, 0.00, 1.57};
const std::string ID           = "EGO";

const double ACCEL   = 4;
const double DECEL   = 2;
const double ANGULAR = 0.5;

}  // namespace Ego

}  // namespace Settings
