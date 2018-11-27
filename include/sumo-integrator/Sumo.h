#ifndef INCLUDE_SUMOINTEGRATOR_SUMO_H
#define INCLUDE_SUMOINTEGRATOR_SUMO_H


#include <lib/sumo/libsumo.h>


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
    class Entities;
    class Simulation;

public:
    using TraCIAPI::vehicle;

    std::unique_ptr<Connection> connection;
    std::unique_ptr<Ego> ego;
    std::unique_ptr<Entities> entities;
    std::unique_ptr<Simulation> simulation;

    ///
    /// @BRIEF  Construct a new Sumo object.
    ///
    Sumo();

    ///
    /// @BRIEF  Destroy the Sumo object.
    ///
    ~Sumo();
};

}  // namespace SumoIntegrator


#endif  // INCLUDE_SUMOINTEGRATOR_SUMO_H
