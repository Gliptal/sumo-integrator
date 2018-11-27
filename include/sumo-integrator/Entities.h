#ifndef INCLUDE_SUMOINTEGRATOR_ENTITIES_H
#define INCLUDE_SUMOINTEGRATOR_ENTITIES_H


#include "include/sumo-integrator/Concern.h"
#include "include/sumo-integrator/Sumo.h"

#include <string>
#include <vector>


namespace SumoIntegrator {

///
/// @AUTHOR            Mattia Affabris - mattia.affabris@antemotion.com
/// @DATE              2018-11-26
/// @VERSION           0.3.0
/// @VERSION           1
/// @COPYRIGHT         Copyright (C) (2018) AnteMotion
///
/// @BRIEF  Wraps entities-related TraCIAPI facilities.
///
/// Handles anything related to SUMO's entities, including obtaining and feeding data related to them.
///
/// @NOTE  May only be accessed as a nested class of `SumoIntegrator::Sumo`.
///
class Sumo::Entities : private Sumo::Concern {
public:
    Entities(TraCIAPI&);
    ~Entities();

    ///
    /// @BRIEF  Subscribe to an entity's data feed.
    ///
    /// Once subscribed to an entity's data feed, on each SUMO simulation tick SUMO makes that data available through
    /// the `get_datafeed()` method.
    ///
    /// @NOTE  Subscriptions cannot be made on not yet spawned entities.
    ///
    /// @WARNING  Subscribing to not yet spawned entities will close the connection with SUMO's server instance.
    ///
    /// @UNITS
    /// `start`  seconds (s)\n
    /// `end`    seconds (s)
    ///
    /// @PARAM[in]      entity   The type of entity whose feed to subscribe to.
    /// @PARAM[in]      id       The `id` of the entity whose feed to subscribe to.
    /// @PARAM[in]      request  The data requested to be in the entity's feed.
    /// @PARAM[in]      start    The time the subscription starts taking effect.
    /// @PARAM[in]      end      The time the subscription stops taking effect.
    ///
    /// @DEBUG
    /// `DEBUG_INFO` - Subscription target.
    ///
    void subscribe(TraCIAPI::TraCIScopeWrapper&, const std::string&, const std::vector<int>&, const double, const double);

    ///
    /// @BRIEF  Get an entity's data feed.
    ///
    /// It is assumed a subscription was previously made with `subscribe()`.
    ///
    /// @PARAM[in]      entity  The type of entity whose feed to obtain.
    /// @PARAM[in]      id      The `id` of the entity whose feed to obtain.
    ///
    /// @RETURN  libsumo::TraCIResults
    ///
    /// @THROWS  libsumo::TraCIException  If no subscription was previously made.
    ///
    /// @DEBUG
    /// `DEBUG_DATA` - Amount of data received from the subscription.
    ///
    libsumo::TraCIResults get_datafeed(TraCIAPI::TraCIScopeWrapper&, const std::string&);
};

}  // namespace SumoIntegrator


#endif  //INCLUDE_SUMOINTEGRATOR_ENTITIES_H
