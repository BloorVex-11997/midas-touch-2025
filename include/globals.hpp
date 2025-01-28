#pragma once

#include "main.h"

const double PI = 3.14159265358979323846;

/** Motor Port Numbers */
const int DRIVETRAIN_PORT_1 = 13;
const int DRIVETRAIN_PORT_2 = 7;
const int DRIVETRAIN_PORT_3 = 1;
const int IMU_PORT = 15;

/** Voltage Limits */
const int ABS_VOLTAGE_LIMIT = 127;
const int TURN_VOLTAGE_LIMIT = 50;

/** Multipliers */
const int TURN_MULTIPLIER = 1;
const double PRECISION_MULTIPLIER = 0.5;

/** Boolean Flags */
const bool DEBUG_MODE = true;

/** Robot Objects */
inline pros::IMU imu_sensor(IMU_PORT);
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);