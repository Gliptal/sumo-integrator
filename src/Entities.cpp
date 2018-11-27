#include "include/sumo-integrator/Entities.h"

#include "include/sumo-integrator/debug.h"

#include <lib/sumo/libsumo.h>


namespace SumoIntegrator {

Sumo::Entities::Entities(TraCIAPI& api)
    : Concern(api) {
}

Sumo::Entities::~Entities() {
}

void Sumo::Entities::subscribe(TraCIAPI::TraCIScopeWrapper& entity, const std::string& id, const std::vector<int>& request, const double start, const double end) {
    entity.subscribe(id, request, start, end);

    LOG_INFO_SUCCESS("subscribed to %s", id.c_str());
}

libsumo::TraCIResults Sumo::Entities::get_datafeed(TraCIAPI::TraCIScopeWrapper& entity, const std::string& id) {
    libsumo::TraCIResults datafeed = entity.getSubscriptionResults(id);

    if (datafeed.empty()) {
        LOG_INFO_FAIL("entity %s not subscribed", id.c_str());

        throw libsumo::TraCIException("entity not subscribed");
    }

    LOG_DATA("received %d data", datafeed.size());

    return datafeed;
}

}  // namespace SumoIntegrator
