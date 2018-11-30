#ifndef INCLUDE_SUMOINTEGRATOR_CORE_SUMO_H
#define INCLUDE_SUMOINTEGRATOR_CORE_SUMO_H


#include <lib/sumo/libsumo.h>


namespace sumointegrator {

///
/// @AUTHOR            Mattia Affabris - mattia.affabris@antemotion.com
/// @DATE              2018-11-14
/// @DATE              2018-11-29
/// @VERSION           0.3.0-alpha3
/// @VERSION           6
/// @COPYRIGHT         Copyright (C) (2018) AnteMotion
///
/// @BRIEF  TraCIAPI client.
///
/// The client side of SUMO's client-server model, this class provides high-level interaction through SUMO's own C++
/// TraCIAPI library. TraCIAPI methods are wrapped into an organic and consistent interface, based on requirements
/// specific to graphics-engine integration.
///
/// Functionality is divided in functionality domains, accessible as pointers to nested classes; each scope groups a
/// specific set of functionality of the client interaction with SUMO:
/// - `Connection`
/// - `Simulation`
/// - `Entities`
/// - `Ego`
///
/// @NOTE  Most `TraCIAPI` objects and methods are _not_ accessible through this class: the corresponding wrapping
///        facilities must be called instead. The following are exceptions:
///        - `TraCIAPI::vehicle`
///
/// @WARNING  In development, major changes are to be expected.
///
class Sumo : private TraCIAPI {
    class Concern;
    class Connection;
    class Ego;
    class Entities;
    class Simulation;

public:
    using TraCIAPI::vehicle;

    ///
    /// @BRIEF  Pointer to the `Connection` domain.
    ///
    /// ```
    /// Sumo sumo;
    /// sumo.connection->open();
    /// ```
    ///
    std::unique_ptr<Connection> connection;

    ///
    /// @BRIEF  Pointer to the `Ego` domain.
    ///
    /// ```
    /// Sumo sumo;
    /// sumo.ego->move();
    /// ```
    ///
    std::unique_ptr<Ego> ego;

    ///
    /// @BRIEF  Pointer to the `Entities` domain.
    ///
    /// ```
    /// Sumo sumo;
    /// sumo.entities->subscribe();
    /// ```
    ///
    std::unique_ptr<Entities> entities;

    ///
    /// @BRIEF  Pointer to the `Simulation` domain.
    ///
    /// ```
    /// Sumo sumo;
    /// sumo.entities->tick();
    /// ```
    ///
    std::unique_ptr<Simulation> simulation;

    ///
    /// @BRIEF  Construct a new `Sumo` object.
    ///
    /// Multiple instances may exist at the same time: each acts as a separate client connected to SUMO's server
    /// instance.
    ///
    Sumo();

    ///
    /// @BRIEF  Destroy the `Sumo` object.
    ///
    ~Sumo();
};

}  // namespace sumointegrator


#endif  // INCLUDE_SUMOINTEGRATOR_CORE_SUMO_H
