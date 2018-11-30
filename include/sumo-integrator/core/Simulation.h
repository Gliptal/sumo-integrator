#ifndef INCLUDE_SUMOINTEGRATOR_CORE_SIMULATION_H
#define INCLUDE_SUMOINTEGRATOR_CORE_SIMULATION_H


#include "include/sumo-integrator/core/Concern.h"
#include "include/sumo-integrator/core/Sumo.h"


namespace sumointegrator {

///
/// @AUTHOR            Mattia Affabris - mattia.affabris@antemotion.com
/// @DATE              2018-11-26
/// @DATE              2018-11-29
/// @VERSION           0.3.0-alpha3
/// @VERSION           2
/// @COPYRIGHT         Copyright (C) (2018) AnteMotion
///
/// @BRIEF  Exposes facilities related to SUMO's simulation.
///
/// Handles anything related to managing SUMO's simulation.
///
/// @NOTE  May only be accessed as a pointer member class of `sumointegrator::Sumo` (`sumointegrator::Sumo::simulation`).
///
class Sumo::Simulation : private Sumo::Concern {
public:
    Simulation(TraCIAPI&);
    ~Simulation();

    ///
    /// @BRIEF  Run a step of SUMO's simulation.
    ///
    /// The length of the time simulated in the step depends on the value passed to SUMO with its `--step-length`
    /// option.
    ///
    /// @NOTE  SUMO halts its simulation until this method is called.
    ///
    /// @DEBUG
    /// `DEBUG_DATA` - Simulation tick.
    ///
    void tick();

    ///
    /// @BRIEF  Run SUMO's simulation up to a given time.
    ///
    /// This is useful in an asynchronous environment, where the client runs independently from SUMO and sends/requests
    /// updates at variable intervals. The client may tick at its own rate, and sync up only when needed by signalling
    /// SUMO to step through its simulation up to the current time.
    ///
    /// @NOTE  SUMO ticks the appropriate amount of times based on the `--step-length` option.
    ///
    /// @UNITS
    /// `time`  seconds (s)
    ///
    /// @PARAM[in]      time  The time up to which SUMO should run its simulation.
    ///
    /// @DEBUG
    /// `DEBUG_DATA` - Simulation tick.
    ///
    void tick(const double);
};

}  // namespace sumointegrator


#endif  //INCLUDE_SUMOINTEGRATOR_CORE_SIMULATION_H
