#ifndef INCLUDE_SUMOINTEGRATOR_TYPES_EXCEPTION_H
#define INCLUDE_SUMOINTEGRATOR_TYPES_EXCEPTION_H


#include <lib/sumo/libsumo.h>


namespace sumointegrator {

namespace types {

///
/// @BRIEF  Generic runtime exception.
///
typedef libsumo::TraCIException RuntimeException;

///
/// @BRIEF  Generic connection exception.
///
typedef tcpip::SocketException ConnectionException;

}  // namespace types

}  // namespace sumointegrator


#endif  // INCLUDE_SUMOINTEGRATOR_TYPES_EXCEPTION_H
