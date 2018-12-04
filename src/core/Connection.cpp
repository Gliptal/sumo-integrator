#include "include/sumo-integrator/core/Connection.h"

#include "include/sumo-integrator/types/exception.h"
#include "include/sumo-integrator/utils/debug.h"

#include <lib/sumo/libsumo.h>

#include <string>


namespace sumointegrator {

Sumo::Connection::Connection(TraCIAPI& api)
    : Concern(api) {
}

Sumo::Connection::~Connection() {
}

void Sumo::Connection::open() {
    connect(server.ip, server.port);
}

void Sumo::Connection::open(const std::string& address) {
    set_address(address);

    connect(server.ip, server.port);
}

void Sumo::Connection::open(const std::string& ip, const uint port) {
    set_address(ip, port);

    connect(server.ip, server.port);
}

void Sumo::Connection::close() {
    if (isConnected) {
        api.close();
        isConnected = false;

        LOG_INFO_SUCCESS("connection closed");
    }
    else {
        LOG_INFO_FAIL("not connected");

        throw types::ConnectionException("not connected");
    }
}

bool Sumo::Connection::status() {
    return isConnected;
}

std::string Sumo::Connection::get_ip() {
    return server.ip;
}

uint Sumo::Connection::get_port() {
    return server.port;
}

void Sumo::Connection::set_address(const std::string& address) {
    server.set(address);
}

void Sumo::Connection::set_address(const std::string& ip, const uint port) {
    server.set(ip, port);
}

void Sumo::Connection::set_ip(const std::string& ip) {
    server.ip = ip;
}

void Sumo::Connection::set_port(const uint port) {
    server.port = port;
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
    catch (types::ConnectionException except) {
        LOG_INFO_FAIL("connecting to %s:%d", ip.c_str(), port);

        throw types::ConnectionException(ip + ":" + std::to_string(port) + " unreachable");
    }
}

}  // namespace sumointegrator
