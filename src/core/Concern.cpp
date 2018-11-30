#include "include/sumo-integrator/core/Concern.h"

#include <lib/sumo/libsumo.h>


namespace sumointegrator {

Sumo::Concern::Concern(TraCIAPI& api)
    : api(api) {
}

Sumo::Concern::~Concern() {
}

}  // namespace sumointegrator
