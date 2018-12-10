#include "include/sumo-integrator/core/Entities.h"

#include "include/sumo-integrator/types/compound.h"
#include "include/sumo-integrator/types/exception.h"
#include "include/sumo-integrator/utils/debug.h"

#include <lib/sumo/libsumo.h>

#include <string>
#include <vector>


namespace sumointegrator {

Sumo::Entities::Entities(TraCIAPI& api)
    : Concern(api) {
}

Sumo::Entities::~Entities() {
}

std::vector<std::string> Sumo::Entities::list_spawning(const bool keep, const std::string& filter) {
    std::vector<std::string> original = api.simulation.getDepartedIDList();
    std::vector<std::string> filtered;

    if (keep) {
        for (auto i = original.begin(); i != original.end(); i++)
            if ((*i).find(filter) != std::string::npos)
                filtered.push_back(*i);
    }
    else {
        for (auto i = original.begin(); i != original.end(); i++)
            if ((*i).find(filter) == std::string::npos)
                filtered.push_back(*i);
    }

    LOG_DATA("spawning %d/%d (filtered)", original.size(), filtered.size());

    return filtered;
}

std::vector<std::string> Sumo::Entities::list_spawning() {
    std::vector<std::string> list = api.simulation.getDepartedIDList();

    LOG_DATA("spawning %d entities", list.size());

    return list;
}

void Sumo::Entities::subscribe(TraCIAPI::TraCIScopeWrapper& entity, const std::string& id, const std::vector<int>& request, const double start, const double end) {
    entity.subscribe(id, request, start, end);

    LOG_INFO_SUCCESS("subscribed to %s", id.c_str());
}

types::Datamap Sumo::Entities::poll(TraCIAPI::TraCIScopeWrapper& entity, const std::string& id) {
    types::Datamap data = entity.getSubscriptionResults(id);

    if (data.empty()) {
        LOG_INFO_FAIL("entity %s not subscribed", id.c_str());

        throw types::RuntimeException("entity not subscribed");
    }

    LOG_DATA("received %d data", data.size());

    return data;
}

}  // namespace sumointegrator
