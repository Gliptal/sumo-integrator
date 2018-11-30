#ifndef INCLUDE_SUMOINTEGRATOR_CORE_ENTITIES_H
#define INCLUDE_SUMOINTEGRATOR_CORE_ENTITIES_H


#include "include/sumo-integrator/core/Concern.h"
#include "include/sumo-integrator/core/Sumo.h"

#include <string>
#include <vector>


namespace sumointegrator {

///
/// @AUTHOR            Mattia Affabris - mattia.affabris@antemotion.com
/// @DATE              2018-11-26
/// @DATE              2018-11-29
/// @VERSION           0.3.0-alpha3
/// @VERSION           3
/// @COPYRIGHT         Copyright (C) (2018) AnteMotion
///
/// @BRIEF  Exposes facilities related to SUMO's entities.
///
/// Handles anything related to SUMO's entities in the current simulation, including obtaining and feeding data.
///
/// @NOTE  May only be accessed as a pointer member class of `sumointegrator::Sumo` (`sumointegrator::Sumo::entities`).
///
class Sumo::Entities : private Sumo::Concern {
public:
    ///
    /// @BRIEF  Provides default datasets to be used with subscriptions.
    ///
    /// - `TRANSFORM`
    /// - `VECTORS`
    /// - `STATE`
    ///
    std::map<std::string, std::vector<int>> DATASETS = {
        {"TRANSFORM", {VAR_POSITION3D, VAR_ANGLE}},
        {"VECTORS", {VAR_SPEED, VAR_ACCELERATION}},
        {"STATE", {VAR_SIGNALS, VAR_STOPSTATE}}};

    Entities(TraCIAPI&);
    ~Entities();

    ///
    /// @BRIEF  Subscribe to an entity's data feed.
    ///
    /// Once subscribed to a data feed, on each SUMO simulation tick that data is made available through
    /// `poll()`.
    ///
    /// @NOTE  Subscriptions cannot be made on not yet spawned entities.
    ///
    /// @WARNING  Attempting to subscribe to not yet spawned entities will terminate SUMO's simulation and close the
    ///           connection with SUMO's server instance.
    ///
    /// @UNITS
    /// `start`  seconds (s)\n
    /// `end`    seconds (s)
    ///
    /// @PARAM[in]      entity   The type of entity whose feed to subscribe to.
    /// @PARAM[in]      id       The `id` of the entity whose feed to subscribe to.
    /// @PARAM[in]      request  The requested data.
    /// @PARAM[in]      start    The time the subscription starts taking effect.
    /// @PARAM[in]      end      The time the subscription stops taking effect.
    ///
    /// @DEBUG
    /// `DEBUG_INFO` - Subscription target.
    ///
    void subscribe(TraCIAPI::TraCIScopeWrapper&, const std::string&, const std::vector<int>&, const double, const double);

    ///
    /// @BRIEF  Poll an entity's data feed.
    ///
    /// It is assumed a subscription was previously made with `subscribe()`. The data is collected in an `std::map`
    /// (`libsumo::TraCIResults`) and can be index-accessed for usage.
    ///
    /// @PARAM[in]      entity  The type of entity whose feed to poll.
    /// @PARAM[in]      id      The `id` of the entity whose feed to poll.
    ///
    /// @RETURN  An `std::map` with all the requested data.
    ///
    /// @THROWS  libsumo::TraCIException  If no subscription was previously made.
    ///
    /// @DEBUG
    /// `DEBUG_DATA` - Number of datapoints received from the subscription.
    ///
    libsumo::TraCIResults poll(TraCIAPI::TraCIScopeWrapper&, const std::string&);
};

}  // namespace sumointegrator


#endif  //INCLUDE_SUMOINTEGRATOR_CORE_ENTITIES_H
