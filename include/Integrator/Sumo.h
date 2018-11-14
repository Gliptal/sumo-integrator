#ifndef INCLUDE_INTEGRATOR_SUMO_H
#define INCLUDE_INTEGRATOR_SUMO_H


#include <lib/sumo/libsumo.h>

#include <string>
#include <vector>


namespace Integrator {

class Sumo : public TraCIAPI {
public:
    enum ENTITY_TYPE { VEHICLE };

    Sumo();
    ~Sumo();

    bool connect(const std::string, const uint);
    void close();
    void tick();

    bool subscribe(const ENTITY_TYPE, const std::string, const std::vector<int>&, const double, const double);
    libsumo::TraCIResults get_data(const ENTITY_TYPE, const std::string);

    void move_ego(const std::string, const Position);
};

}  // namespace Integrator


#endif  // INCLUDE_INTEGRATOR_SUMO_H
