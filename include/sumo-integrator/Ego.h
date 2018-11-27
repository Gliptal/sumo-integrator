#ifndef INCLUDE_SUMOINTEGRATOR_EGO_H
#define INCLUDE_SUMOINTEGRATOR_EGO_H


#include "include/sumo-integrator/Concern.h"
#include "include/sumo-integrator/Sumo.h"

#include <string>


namespace SumoIntegrator {

///
/// @AUTHOR            Mattia Affabris - mattia.affabris@antemotion.com
/// @DATE              2018-11-26
/// @VERSION           0.3.0
/// @VERSION           1
/// @COPYRIGHT         Copyright (C) (2018) AnteMotion
///
/// @BRIEF  Wraps ego-related TraCIAPI facilities.
///
/// Handles the ego entity within SUMO's simulation. It is assumed only one "main" ego entity exists, although it is
/// possible to alter other entities state as if they were ego entities themselves.
///
/// @NOTE  May only be accessed as a nested class of `SumoIntegrator::Sumo`.
///
class Sumo::Ego : private Sumo::Concern {
public:
    Ego(TraCIAPI&);
    ~Ego();

    ///
    /// @BRIEF  Position an ego entity.
    ///
    /// The ego entity is placed in the given coordinates, with no interpolation/extrapolation made on its state
    /// vectors. SUMO is capable of interacting with the ego entity based on position alone.
    ///
    /// @NOTE  The ego entity's SUMO `id` must be set first via `set_id()`.
    ///
    /// @PARAM[in]      position  The target `3D` position.
    ///
    /// @THROWS  libsumo::TraCIException  If the `id` is not set.
    ///
    /// @SEE `move(const std::string&, const Position&)`
    ///
    void move(const Position&);

    ///
    /// @BRIEF  Position an ego entity.
    ///
    /// An entity identified by its `id` is placed in the given coordinates, with no interpolation/extrapolation made on
    /// its state vectors. This method is useful to move non-ego entities as if they were such.
    ///
    /// @PARAM[in]      id        The `id` of the ego entity.
    /// @PARAM[in]      position  The target `3D` position.
    ///
    /// @SEE `move(const Position&)`
    ///
    void move(const std::string&, const Position&);

    ///
    /// @BRIEF  Get the set `id` of the ego entity.
    ///
    /// @RETURN  The currently set `id`.
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

}  // namespace SumoIntegrator


#endif  //INCLUDE_SUMOINTEGRATOR_EGO_H
