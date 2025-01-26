#pragma once
#include "main.h"

const double PI = 3.14159265358979323846;

// Motor port numbers
const int DRIVETRAIN_PORT_1 = 13;
const int DRIVETRAIN_PORT_2 = 7;
const int DRIVETRAIN_PORT_3 = 1;

const int ABS_VOLTAGE_LIMIT = 127;

const int TURN_VOLTAGE_LIMIT = 50;
const int TURN_MULTIPLIER = 1;

inline pros::IMU imu_sensor(15);