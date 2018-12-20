#ifndef INCLUDE_SUMOINTEGRATOR_CORE_CONNECTION_H
#define INCLUDE_SUMOINTEGRATOR_CORE_CONNECTION_H


#include "include/sumo-integrator/core/Concern.h"
#include "include/sumo-integrator/core/Sumo.h"

#include <string>


namespace sumointegrator {

///
/// @AUTHOR            Mattia Affabris - mattia.affabris@antemotion.com
/// @DATE              2018-11-23
/// @MODDATE           2018-11-29
/// @VERSION           0.4.0-alpha4
/// @MODVERSION        2
/// @COPYRIGHT         Copyright (C) (2018) AnteMotion
///
/// @BRIEF  Exposes facilities related to the client-SUMO connection.
///
/// Handles the network connection between SUMO and (this) client. The OS hosting SUMO must reside on a LAN or WAN
/// network, and be reachable through IPv4; SUMO must be running as a server instance (see its `--remote-port` option)
/// before any attempts at interaction are made. The network layer uses the TCP protocol and packets are encoded, sent,
/// and received by TraCIAPI internals.
///
/// @NOTE  May only be accessed as a pointer member of `sumointegrator::Sumo` (`sumointegrator::Sumo::connection`).
///
class Sumo::Connection : private Sumo::Concern {
public:
    Connection(TraCIAPI&);
    ~Connection();

    ///
    /// @BRIEF  Connect to a SUMO server instance.
    ///
    /// The instance may be running on a different hardware or virtual machine, but must be reachable through WAN or
    /// LAN. If IP and port were not previously set with the `set_address()`, or `set_ip()` and `set_port()`, the
    /// default `127.0.0.1:6666` address is used.
    ///
    /// @THROWS  types::ConnectionException  If a connection could not be established.
    ///
    /// @DEBUG
    /// `DEBUG_INFO` - Attempt at opening the connection.
    ///
    /// @SEE  `open(const std::string&)`
    /// @SEE  `open(const std::string&, const uint)`
    ///
    void open();

    ///
    /// @BRIEF  Connect to a SUMO server instance.
    ///
    /// The instance may be running on a different hardware or virtual machine, but must be reachable through WAN or
    /// LAN.
    ///
    /// @PARAM[in]      address  The network address of the machine hosting the SUMO instance, in "standard" IPv4 format
    ///                          with an appended process port (`x.x.x.x:n`).
    ///
    /// @THROWS  types::ConnectionException  If a connection could not be established.
    ///
    /// @DEBUG
    /// `DEBUG_INFO` - Attempt at opening the connection.
    ///
    /// @SEE  `open()`
    /// @SEE  `open(const std::string&, const uint)`
    ///
    void open(const std::string&);

    ///
    /// @BRIEF  Connect to a SUMO server instance.
    ///
    /// The instance may be running on a different hardware or virtual machine, but must be reachable through WAN or
    /// LAN.
    ///
    /// @PARAM[in]      ip    The IP of the machine hosting the SUMO instance, in "standard" IPv4 format (`x.x.x.x`).
    /// @PARAM[in]      port  The process port number of the SUMO instance (see its `--remote-port` option).
    ///
    /// @THROWS  types::ConnectionException  If a connection could not be established.
    ///
    /// @DEBUG
    /// `DEBUG_INFO` - Attempt at opening the connection.
    ///
    /// @SEE  `open()`
    /// @SEE  `open(const std::string&)`
    ///
    void open(const std::string&, const uint);

    ///
    /// @BRIEF  Close the connection to SUMO's server instance.
    ///
    /// A signal is also sent to SUMO's server instance, requesting the termination of its simulation.
    ///
    /// @THROWS  types::ConnectionException  If no connection exists.
    ///
    /// @DEBUG
    /// `DEBUG_INFO` - Closing the connection.
    ///
    void close();

    ///
    /// @BRIEF  Obtain the current status of the connection.
    ///
    /// This checks if an `open()` call was previously successfully and no `close()` has been called since. No check is
    /// actually made on the low-level state of the network connection.
    ///
    /// @WARNING  Do not use this as assurance that the TCP/IP connection is working.
    ///
    /// @RETURN  `true` if the connection is open, `false` otherwise.
    ///
    bool status();

    ///
    /// @BRIEF  Get the IP of SUMO's server instance.
    ///
    /// The IP is in "standard" IPv4 format (`x.x.x.x`). It defaults to `127.0.0.1`, and may be explicitly set with
    /// `set_ip()` or `set_address()`.
    ///
    /// @RETURN  The IP of SUMO's server instance.
    ///
    std::string get_ip();

    ///
    /// @BRIEF  Get the process port of SUMO's server instance.
    ///
    /// Defaults to `6666`, and may be explicitly set with `set_port()` or `set_address()`.
    ///
    /// @RETURN  The process port of SUMO's server instance.
    ///
    uint get_port();

    ///
    /// @BRIEF  Set SUMO's server instance address.
    ///
    /// The instance may be running on a different hardware or virtual machine, but must be reachable through WAN or
    /// LAN.
    ///
    /// @PARAM[in]      address  The network address of the machine hosting the SUMO instance, in "standard" IPv4 format
    ///                          with an appended process port (`x.x.x.x:n`).
    ///
    /// @SEE `set_address(const std::string&, const uint)`
    ///
    void set_address(const std::string&);

    ///
    /// @BRIEF  Set the address of SUMO's server instance.
    ///
    /// The instance may be running on a different hardware or virtual machine, but must be reachable through WAN or
    /// LAN.
    ///
    /// @PARAM[in]      ip    The IP of the machine hosting the SUMO instance, in "standard" IPv4 format (`x.x.x.x`).
    /// @PARAM[in]      port  The process port number of the SUMO instance (see its `--remote-port` option).
    ///
    /// @SEE `set_address(const std::string&)`
    ///
    void set_address(const std::string&, const uint);

    ///
    /// @BRIEF  Set the IP of SUMO's server instance.
    ///
    /// @PARAM[in]      ip  The IP of the machine hosting the SUMO instance, in "standard" IPv4 format (`x.x.x.x`).
    ///
    void set_ip(const std::string&);

    ///
    /// @BRIEF  Set the process port of SUMO's server instance.
    ///
    /// @PARAM[in]      port  The process port number of the SUMO instance (see its `--remote-port` option).
    ///
    void set_port(const uint);

private:
    struct address_t {
    public:
        std::string ip = "127.0.0.1";
        uint port      = 6666;

        void set(const std::string& ip, const uint port);
        void set(const std::string& address);
    } server;

    bool isConnected = false;

    void connect(const std::string&, const uint);
};

}  // namespace sumointegrator


#endif  // INCLUDE_SUMOINTEGRATOR_CORE_CONNECTION_H
