#include "include/sumo-integrator/Connection.h"

#include "include/sumo-integrator/debug.h"

#include <lib/sumo/libsumo.h>

#include <string>


namespace SumoIntegrator {

Sumo::Connection::Connection(TraCIAPI& api)
    : api(api) {
}

Sumo::Connection::~Connection() {
}

void Sumo::Connection::open() {
    connect(sumoAddress.ip, sumoAddress.port);
}

void Sumo::Connection::open(const std::string& address) {
    set_address(address);

    connect(sumoAddress.ip, sumoAddress.port);
}

void Sumo::Connection::open(const std::string& ip, const uint port) {
    set_address(ip, port);

    connect(sumoAddress.ip, sumoAddress.port);
}

void Sumo::Connection::close() {
    if (isConnected) {
        api.close();
        isConnected = false;

        LOG_INFO_SUCCESS("connection closed");
    }
    else {
        LOG_INFO_FAIL("not connected");

        throw tcpip::SocketException("");
    }
}

bool Sumo::Connection::status() {
    return isConnected;
}

std::string Sumo::Connection::get_ip() {
    return sumoAddress.ip;
}

uint Sumo::Connection::get_port() {
    return sumoAddress.port;
}

void Sumo::Connection::set_address(const std::string& address) {
    sumoAddress.set(address);
}

void Sumo::Connection::set_address(const std::string& ip, const uint port) {
    sumoAddress.set(ip, port);
}

void Sumo::Connection::set_ip(const std::string& ip) {
    sumoAddress.ip = ip;
}

void Sumo::Connection::set_port(const uint port) {
    sumoAddress.port = port;
}

void Sumo::Connection::address_t::set(const std::string& address) {
    std::size_t colon = address.find(":");

    ip   = address.substr(0, colon);
    port = std::stoi(address.substr(colon + 1));
}

void Sumo::Connection::address_t::set(const std::string& ip, const uint port) {
    this->ip   = ip;
    this->port = port;
}

void Sumo::Connection::connect(const std::string& ip, const uint port) {
    try {
        api.connect(ip, port);
        isConnected = true;

        LOG_INFO_SUCCESS("connected to %s:%d", ip.c_str(), port);
    }
    catch (tcpip::SocketException except) {
        LOG_INFO_FAIL("connecting to %s:%d", ip.c_str(), port);

        throw;
    }
}

}  // namespace SumoIntegrator
