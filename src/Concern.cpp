#include "include/sumo-integrator/Concern.h"

#include <lib/sumo/libsumo.h>


namespace SumoIntegrator {

Sumo::Concern::Concern(TraCIAPI& api)
    : api(api) {
}

Sumo::Concern::~Concern() {
}

}  // namespace SumoIntegrator
