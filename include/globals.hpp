#pragma once

#include "main.h"

const double PI = 3.14159265358979323846;

/** Motor Port Numbers */
const int DRIVETRAIN_PORT_1 = 13;
const int DRIVETRAIN_PORT_2 = 7;
const int DRIVETRAIN_PORT_3 = 1;
const int ELEVATOR_PORT_1 = 3;
const int ELEVATOR_PORT_2 = 4;  // TODO
const int IMU_PORT = 15;
const int CLAMP_PORT = 5;  // TODO

/** Voltage Limits - [-127, 127] */
const int ABS_VOLTAGE_LIMIT = 127;
const int TURN_VOLTAGE_LIMIT = 27;
const int BELT_SPEED = 127;
const int CLAMP_SPEED = 50;

/** Multipliers */
const int TURN_MULTIPLIER = 1;
const double PRECISION_MULTIPLIER = 0.5;

/** Durations */
const int CLAMP_ACTIVE_DURATION = 2000;        // in ms
const int ELEVATOR_EXTENSION_DURATION = 1000;  // in ms
const int AUTO_DURATION = 1500;

/** Boolean Flags */
const bool DEBUG_MODE = true;

/** Robot Objects */
inline pros::IMU imu_sensor(IMU_PORT);
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);