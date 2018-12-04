#include "include/sumo-integrator/types/base.h"

#include <lib/sumo/libsumo.h>

#include <memory>


namespace sumointegrator {

namespace types {

int cast_int(std::shared_ptr<Data> data) {
    return ((libsumo::TraCIInt*) data.get())->value;
}

double cast_double(std::shared_ptr<Data> data) {
    return ((libsumo::TraCIDouble*) data.get())->value;
}

}  // namespace types

}  // namespace sumointegrator
