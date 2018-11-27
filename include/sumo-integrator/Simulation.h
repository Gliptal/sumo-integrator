#ifndef INCLUDE_SUMOINTEGRATOR_SIMULATION_H
#define INCLUDE_SUMOINTEGRATOR_SIMULATION_H


#include "include/sumo-integrator/Concern.h"
#include "include/sumo-integrator/Sumo.h"


namespace SumoIntegrator {

///
/// @AUTHOR            Mattia Affabris - mattia.affabris@antemotion.com
/// @DATE              2018-11-26
/// @VERSION           0.3.0
/// @VERSION           1
/// @COPYRIGHT         Copyright (C) (2018) AnteMotion
///
/// @BRIEF  Wraps simulation-related TraCIAPI facilities.
///
/// Handles anything related to SUMO's simulation.
///
/// @NOTE  May only be accessed as a nested class of `SumoIntegrator::Sumo`.
///
class Sumo::Simulation : private Sumo::Concern {
public:
    Simulation(TraCIAPI&);
    ~Simulation();

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
};

}  // namespace SumoIntegrator


#endif  //INCLUDE_SUMOINTEGRATOR_SIMULATION_H
