#ifndef INCLUDE_SUMOINTEGRATOR_CONNECTION_H
#define INCLUDE_SUMOINTEGRATOR_CONNECTION_H


#include "include/sumo-integrator/Sumo.h"

#include <string>


namespace SumoIntegrator {

///
/// @AUTHOR            Mattia Affabris - mattia.affabris@antemotion.com
/// @DATE              2018-11-23
/// @VERSION           0.3.0
/// @VERSION           1
/// @COPYRIGHT         Copyright (C) (2018) AnteMotion
///
/// @BRIEF  Wraps connection-related TraCIAPI facilities.
///
/// Handles the network connection with SUMO, additionally storing related data on SUMO's network address and the
/// network's state.
///
/// @NOTE  May only be accessed as a nested class of `SumoIntegrator::Sumo`.
///
class Sumo::Connection {
public:
    Connection(TraCIAPI&);
    ~Connection();

    ///
    /// @BRIEF  Connect to a SUMO server instance.
    ///
    /// The instance may be running on a different machine/OS, but must be reachable through WAN or LAN. If `IP` and
    /// port have not been set with the `set_address()` or `set_ip()` and `set_port()`, the default `127.0.0.1:6666` is
    /// used.
    ///
    /// @THROWS  tcpip::SocketException  If a connection could not be established.
    ///
    /// @DEBUG
    /// `DEBUG_INFO` - Attempt at opening the connection.
    ///
    /// @SEE  `open(const std::string&, const uint)`
    /// @SEE  `open(const std::string&)`
    ///
    void open();

    ///
    /// @BRIEF  Connect to a SUMO server instance.
    ///
    /// The instance may be running on a different machine/OS, but must be reachable through WAN or LAN.
    ///
    /// @PARAM[in]      address  The address of the machine hosting the SUMO instance, in "standard" `IPv4` format with
    ///                          an appended port (`x.x.x.x:n`).
    ///
    /// @THROWS  tcpip::SocketException  If a connection could not be established.
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
    /// The instance may be running on a different machine/OS, but must be reachable through WAN or LAN.
    ///
    /// @PARAM[in]      ip    `IP` of the machine hosting the SUMO instance, in "standard" `IPv4` format (`x.x.x.x`).
    /// @PARAM[in]      port  Port number of the SUMO server process running on the hosting machine (SUMO's
    ///                       `--remote-port` option).
    ///
    /// @THROWS  tcpip::SocketException  If a connection could not be established.
    ///
    /// @DEBUG
    /// `DEBUG_INFO` - Attempt at opening the connection.
    ///
    /// @SEE  `open()`
    /// @SEE  `open(const std::string&)`
    ///
    void open(const std::string&, const uint);

    ///
    /// @BRIEF  Close the connection to SUMO's server instance, provided one exists.
    ///
    /// @DEBUG
    /// `DEBUG_INFO` - Closing the connection.
    ///
    void close();

    ///
    /// @BRIEF  Obtain the current status of the connection.
    ///
    /// @RETURN  `true` if the connection is open, `false` otherwise.
    ///
    bool status();

    ///
    /// @BRIEF  Get the set for SUMO's server instance.
    ///
    /// The `IP` is in "standard" `IPv4` format (`x.x.x.x`). If not explicitly set with `set_ip()` or `set_address()`,
    /// it defaults to `127.0.0.1`.
    ///
    /// @RETURN  The currently set `IP`.
    ///
    std::string get_ip();

    ///
    /// @BRIEF  Get the port set for SUMO's server instance. If not explicitly set with `set_port()` or `set_address()`,
    /// it defaults to 6666.
    ///
    /// @RETURN  The currently set port.
    ///
    uint get_port();

    ///
    /// @BRIEF  Set the address of SUMO's server instance.
    ///
    /// The instance may be running on a different machine/OS, but must be reachable through WAN or LAN.
    ///
    /// @PARAM[in]      address  The address of the machine hosting the SUMO instance, in "standard" `IPv4` format with
    ///                          an appended port (`x.x.x.x:n`).
    ///
    /// @SEE `set_address(const std::string&, const uint)`
    ///
    void set_address(const std::string&);

    ///
    /// @BRIEF  Set the address of SUMO's server instance.
    ///
    /// The instance may be running on a different machine/OS, but must be reachable through WAN or LAN.
    ///
    /// @PARAM[in]      ip    `IP` of the machine hosting the SUMO instance, in "standard" `IPv4` format (`x.x.x.x`).
    /// @PARAM[in]      port  Port number of the SUMO server process running on the hosting machine (SUMO's
    ///                       `--remote-port` option).
    ///
    /// @SEE `set_address(const std::string&)`
    ///
    void set_address(const std::string&, const uint);

    ///
    /// @BRIEF  Set the `IP` of SUMO's server instance.
    ///
    /// @PARAM[in]      ip  `IP` of the machine hosting the SUMO instance, in "standard" `IPv4` format (`x.x.x.x`).
    ///
    void set_ip(const std::string&);

    ///
    /// @BRIEF  Set the port of SUMO's server instance.
    ///
    /// @PARAM[in]      port  Port number of the SUMO server process running on the hosting machine (SUMO's
    ///                       `--remote-port` option).
    ///
    void set_port(const uint);

private:
    struct address_t {
    public:
        std::string ip = "127.0.0.1";
        uint port      = 6666;

        void set(const std::string& ip, const uint port);
        void set(const std::string& address);
    } sumoAddress;

    TraCIAPI& api;

    bool isConnected = false;

    void connect(const std::string&, const uint);
};

}  // namespace SumoIntegrator


#endif  // INCLUDE_SUMOINTEGRATOR_CONNECTION_H
