#ifndef INCLUDE_SUMOINTEGRATOR_CORE_EGO_H
#define INCLUDE_SUMOINTEGRATOR_CORE_EGO_H


#include "include/sumo-integrator/core/Concern.h"
#include "include/sumo-integrator/core/Sumo.h"

#include <string>


namespace sumointegrator {

///
/// @AUTHOR            Mattia Affabris - mattia.affabris@antemotion.com
/// @DATE              2018-11-26
/// @DATE              2018-11-29
/// @VERSION           0.3.1-alpha3
/// @VERSION           2
/// @COPYRIGHT         Copyright (C) (2018) AnteMotion
///
/// @BRIEF  Exposes facilities related to the ego entity.
///
/// Handles the ego entity within SUMO's simulation. It is assumed only one "main" ego entity exists, although it is
/// possible to alter the state of other entities as if they were ego entities themselves.
///
/// @NOTE  May only be accessed as a pointer member class of `sumointegrator::Sumo` (`sumointegrator::Sumo::ego`).
///
class Sumo::Ego : private Sumo::Concern {
public:
    Ego(TraCIAPI&);
    ~Ego();

    ///
    /// @BRIEF  Move an ego entity.
    ///
    /// The ego entity is placed at the given coordinates, with no interpolation or extrapolation made on its state
    /// vectors between subsequent `move()`s. SUMO is capable of interacting with this ego entity based on (subsequent)
    /// position(s) alone.
    ///
    /// @NOTE  The `id` of the SUMO entity acting as the ego entity must be set first with `set_id()`.
    ///
    /// @UNITS
    /// `position`  meters (m), meters (m), meters (m)
    ///
    /// @PARAM[in]      position  The target `3D` position.
    ///
    /// @THROWS  libsumo::TraCIException  If the `id` is not set.
    ///
    /// @SEE `move(const std::string&, const Position&)`
    ///
    void move(const Position&);

    ///
    /// @BRIEF  Move an ego entity.
    ///
    /// The SUMO entity identified by its `id` is placed in the given coordinates, with no interpolation or
    /// extrapolation made on its state vectors between subsequent `move(const std::string&, const Position&)`. This
    /// method is useful to move entities other than the "main" ego.
    ///
    /// @UNITS
    /// `position`  meters (m), meters (m), meters (m)
    ///
    /// @PARAM[in]      id        The `id` of the SUMO entity.
    /// @PARAM[in]      position  The target `3D` position.
    ///
    /// @SEE `move(const Position&)`
    ///
    void move(const std::string&, const Position&);

    ///
    /// @BRIEF  Get the `id` of the ego entity.
    ///
    /// @RETURN  The `id` of the ego entity.
    ///
    std::string get_id();

    ///
    /// @BRIEF  Set the `id` of the ego entity.
    ///
    /// @PARAM[in]      id  The `id` of the ego entity.
    ///
    void set_id(const std::string&);

private:
    std::string id;
};

}  // namespace sumointegrator


#endif  //INCLUDE_SUMOINTEGRATOR_CORE_EGO_H
