#ifndef INCLUDE_SUMOINTEGRATOR_SUMO_H
#define INCLUDE_SUMOINTEGRATOR_SUMO_H


#include <lib/sumo/libsumo.h>

#include <string>
#include <vector>


namespace SumoIntegrator {

///
/// @AUTHOR            Mattia Affabris - mattia.affabris@antemotion.com
/// @DATE              2018-11-14
/// @VERSION           0.3.0
/// @VERSION           5
/// @COPYRIGHT         Copyright (C) (2018) AnteMotion
///
/// @BRIEF  Wraps the TraCIAPI library.
///
/// Provides high-level, generic functionality to use SUMO's C++ TraCIAPI library. All TraCIAPI methods are wrapped into
/// an organic and consistent interface, based on integration development requirements.
///
/// @NOTE  Major changes are to be expected.
///
class Sumo : private TraCIAPI {
    class Concern;
    class Connection;
    class Ego;

public:
    using TraCIAPI::vehicle;

    ///
    /// @BRIEF  Construct a new Sumo object.
    ///
    Sumo();

    ///
    /// @BRIEF  Destroy the Sumo object.
    ///
    ~Sumo();

    std::unique_ptr<Connection> connection;
    std::unique_ptr<Ego> ego;

    ///
    /// @BRIEF  Run one step of SUMO's simulation.
    ///
    /// The length of time simulated depends on the value passed to SUMO through the `--step-length` option.
    ///
    /// @NOTE  SUMO halts its simulation until this method is called.
    ///
    /// @DEBUG
    /// `DEBUG_DATA` - Simulation tick.
    ///
    void tick();

    ///
    /// @BRIEF  Run the SUMO simulation up to a given time.
    ///
    /// This is useful in an asynchronous environment, where the client runs independently from SUMO and sends/requests
    /// updates at unknown intervals. The client may tick at its own rate, and sync up by when needed by signalling SUMO
    /// to tick up to the current time.
    ///
    /// @NOTE  This assumes SUMO's clock is synchronized with the client's (or in any case, with the time passed as
    ///        parameter).
    ///
    /// @NOTE  SUMO does _not_ tick once to reach the specified simulation time, but rather the appropriate amount of
    ///        times based on the `--step-length` option.
    ///
    /// @PARAM[in]      time  The time up to which SUMO should simulate (or "sync up to").
    ///
    /// @DEBUG
    /// `DEBUG_DATA` - Simulation tick.
    ///
    void tick(const double);

    ///
    /// @BRIEF  Subscribe to an entity's data feed.
    ///
    /// Once subscribed to an entity's data feed, on each SUMO simulation tick SUMO makes that data available through
    /// the `get_datafeed()` method.
    ///
    /// @NOTE  Subscriptions cannot be made on not yet spawned entities.
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
    /// @TODO Catch exception.
    ///
    void subscribe(TraCIAPI::TraCIScopeWrapper&, const std::string&, const std::vector<int>&, const double, const double);

    ///
    /// @BRIEF  Get an entity's data feed.
    ///
    /// It is assumed a subscription was previously made with `subscribe()`.
    ///
    /// @WARNING  Data feeds returned from unsubscribed entities result in undefined behaviour.
    ///
    /// @PARAM[in]      entity  The type of entity whose feed to obtain.
    /// @PARAM[in]      id      The `id` of the entity whose feed to obtain.
    ///
    /// @RETURN  libsumo::TraCIResults
    ///
    /// @DEBUG
    /// `DEBUG_DATA` - Amount of data received from the subscription.
    ///
    /// @TODO Catch exception.
    ///
    libsumo::TraCIResults get_datafeed(TraCIAPI::TraCIScopeWrapper&, const std::string&);

    ///
    /// @BRIEF  Position an ego vehicle.
    ///
    /// SUMO is capable of interacting with an ego vehicle moved in real time by an external source. The ego vehicle is
    /// precisely placed in the give coordinates, and no interpolation/extrapolation is made on its state vectors.
    ///
    /// @PARAM[in]      id        The `id` of the ego vehicle.
    /// @PARAM[in]      position  The target `3D` position.
    ///
    void move_ego(const std::string&, const Position&);
};

}  // namespace SumoIntegrator


#endif  // INCLUDE_SUMOINTEGRATOR_SUMO_H
