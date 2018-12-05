#include "test/drivers/InputDriver.h"

#include <curses.h>


namespace test {

InputDriver::InputDriver(const double tickrate)
    : Driver(tickrate) {
}

InputDriver::~InputDriver() {
}

void InputDriver::load_network(const double network[][3], const size_t nodes) {
    for (size_t i = 0; i < nodes; i++)
        this->network.push_back({network[i][0], network[i][1], network[i][2]});
}

void InputDriver::set_spawn(const double x, const double y, const double z) {
    position.x = x;
    position.y = y;
    position.z = z;

    for (size_t i = 0; i < 8; i++) {
        if (i == NORTH_RIGHT || i == NORTH_LEFT || i == SOUTH_RIGHT || i == SOUTH_LEFT) {
            if (position.y == network[i][1]) {
                lane = (LANE) i;
                return;
            }
        }
        else {
            if (position.x == network[i][0]) {
                lane = (LANE) i;
                return;
            }
        }
    }
}

void InputDriver::catch_input(const double delta) {
    initscr();
    halfdelay(tickrate > 0.1 ? tickrate * 10 : 1);
    noecho();

    switch (getch()) {
        case 'w':
            speed += delta;
            break;
        case 's':
            speed -= delta;
            break;
        case 'a':
            switch_lane(true);
            break;
        case 'd':
            switch_lane(false);
            break;
        default:
            break;
    }

    endwin();
}

void InputDriver::tick() {
    follow_turn();
    follow_lane();
    drive_straight(speed * tickrate);
}

void InputDriver::switch_lane(const bool overtake) {
    if (!overtake && lane % 2 == 0)
        return;
    if (overtake && lane % 2 != 0)
        return;

    if (lane % 2 == 0)
        lane = (LANE)(lane + 1);
    else
        lane = (LANE)(lane - 1);
}

void InputDriver::drive_straight(const double delta) {
    switch (lane) {
        case NORTH_RIGHT:
        case NORTH_LEFT:
            position.x += delta;
            break;
        case SOUTH_RIGHT:
        case SOUTH_LEFT:
            position.x -= delta;
            break;
        case EAST_RIGHT:
        case EAST_LEFT:
            position.y -= delta;
            break;
        case WEST_RIGHT:
        case WEST_LEFT:
            position.y += delta;
            break;
    }
}

void InputDriver::follow_turn() {
    int next = (lane + 2) % 8;
    int prev = (8 + lane - 2) % 8;

    switch (lane) {
        case NORTH_RIGHT:
        case NORTH_LEFT:
            if (position.x >= network[next][0]) {
                position.x = network[next][0];
                lane       = (LANE) next;
            }
            if (position.x <= network[prev][0]) {
                position.x = network[prev][0];
                lane       = (LANE) prev;
            }
            break;
        case SOUTH_RIGHT:
        case SOUTH_LEFT:
            if (position.x <= network[next][0]) {
                position.x = network[next][0];
                lane       = (LANE) next;
            }
            if (position.x >= network[prev][0]) {
                position.x = network[prev][0];
                lane       = (LANE) prev;
            }
            break;
        case EAST_RIGHT:
        case EAST_LEFT:
            if (position.y <= network[next][1]) {
                position.y = network[next][1];
                lane       = (LANE) next;
            }
            if (position.y >= network[prev][1]) {
                position.y = network[prev][1];
                lane       = (LANE) prev;
            }
            break;
        case WEST_RIGHT:
        case WEST_LEFT:
            if (position.y >= network[next][1]) {
                position.y = network[next][1];
                lane       = (LANE) next;
            }
            if (position.y <= network[prev][1]) {
                position.y = network[prev][1];
                lane       = (LANE) prev;
            }
            break;
    }
}

void InputDriver::follow_lane() {
    switch (lane) {
        case NORTH_RIGHT:
        case NORTH_LEFT:
        case SOUTH_RIGHT:
        case SOUTH_LEFT:
            position.y = network[lane][1];
            break;
        case EAST_RIGHT:
        case EAST_LEFT:
        case WEST_RIGHT:
        case WEST_LEFT:
            position.x = network[lane][0];
            break;
    }
}


}  // namespace test
