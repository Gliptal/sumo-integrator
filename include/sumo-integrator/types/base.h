#ifndef INCLUDE_SUMOINTEGRATOR_TYPES_BASE_H
#define INCLUDE_SUMOINTEGRATOR_TYPES_BASE_H


#include <lib/sumo/libsumo.h>

#include <memory>


namespace sumointegrator {

namespace types {

///
/// @BRIEF  Generic data container.
///
/// May contain a number of different data types: use the provided functions to cast to built-in standard types for
/// usage.
///
/// @SEE  `cast_int()`
/// @SEE  `cast_double()`
///
typedef libsumo::TraCIResult Data;

///
/// @BRIEF  Cast to a standard `int`.
///
/// @PARAM[in]      data  An `std::shared_ptr` to some generic Data.
///
/// @RETURN  The corresponding standard `int`.
///
int cast_int(const std::shared_ptr<Data>);

///
/// @BRIEF  Cast to a standard `double`.
///
/// @PARAM[in]      data  An `std::shared_ptr` to some generic Data.
///
/// @RETURN  The corresponding standard `double`.
///
double cast_double(const std::shared_ptr<Data>);

}  // namespace types

}  // namespace sumointegrator


#endif  // INCLUDE_SUMOINTEGRATOR_TYPES_BASE_H
