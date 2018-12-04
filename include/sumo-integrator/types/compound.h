#ifndef INCLUDE_SUMOINTEGRATOR_TYPES_COMPOUND_H
#define INCLUDE_SUMOINTEGRATOR_TYPES_COMPOUND_H


#include <lib/sumo/libsumo.h>


namespace sumointegrator {

namespace types {

///
/// @BRIEF  A 3D position.
///
/// `x`, `y`, and `z` coordinates are saved as `double` and accessible directly.
///
typedef libsumo::TraCIPosition Position;

///
/// @BRIEF  `std::map` of generic `Data`.
///
typedef libsumo::TraCIResults Datamap;

///
/// @BRIEF  `std::map` of `Datamaps`.
///
typedef libsumo::SubscriptionResults Datamaps;

}  // namespace types

}  // namespace sumointegrator


#endif  // INCLUDE_SUMOINTEGRATOR_TYPES_COMPOUND_H
