#include <string>


namespace Settings {

namespace Network {

const std::string IP = "127.0.0.1";
const uint PORT      = 6666;

}  // namespace Network

namespace Simulation {

const double TICKRATE = 0.010;
const double END_TIME = 120;

}  // namespace Simulation

namespace Traffic {

const std::string ID    = "traffic.0";
const double START_TIME = 4;

}  // namespace Traffic

}  // namespace Settings
