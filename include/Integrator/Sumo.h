#ifndef INCLUDE_INTEGRATOR_SUMO_H
#define INCLUDE_INTEGRATOR_SUMO_H


#include <lib/sumo/libsumo.h>

#include <string>
#include <vector>


namespace Integrator {

///
/// @AUTHOR            Mattia Affabris - mattia.affabris@antemotion.com
/// @DATE              2018-11-14
/// @VERSION           0.2.0
/// @VERSION           3
/// @COPYRIGHT         Copyright (C) (2018) AnteMotion
///
/// @BRIEF  Wraps common TraCIAPI functions.
///
/// Provides high-level, generic functionality to use SUMO's C++ TraCIAPI library. All TraCIAPI methods are wrapped into
/// an organic and consistent interface, based on integration development requirements.
///
/// @NOTE  Major changes are to be expected.
///
class Sumo : public TraCIAPI {
public:
    ///
    /// @BRIEF  Construct a new Sumo object.
    ///
    Sumo();

    ///
    /// @BRIEF  Destroy the Sumo object.
    ///
    ~Sumo();

    ///
    /// @BRIEF  Connects to a SUMO server instance.
    ///
    /// The instance may be running on a different machine/OS, but must be reachable through WAN or LAN.
    ///
    /// @PARAM[in]      ip    `IP` of the machine hosting the SUMO instance, in "standard" `IPv4` format (`x.x.x.x`).
    /// @PARAM[in]      port  Port number of the SUMO server process running on the hosting machine (SUMO's
    ///                       `--remote-port` option).
    ///
    /// @THROWS         tcpip::SocketException  If a connection could not be established.
    ///
    /// @DEBUG
    /// `DEBUG_INFO` - Attempt at opening the connection.
    ///
    void connect(const std::string&, const uint);

    ///
    /// @BRIEF  Closes the connection to SUMO's server instance.
    ///
    /// @DEBUG
    /// `DEBUG_INFO` - Closing the connection.
    ///
    void close();

    ///
    /// @BRIEF  Runs one step of SUMO's simulation.
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
    /// @BRIEF  Subscribes to an entity's data feed.
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

}  // namespace Integrator


#endif  // INCLUDE_INTEGRATOR_SUMO_H
