#pragma once

#include "main.h"

/**
 * Run synchronously with the main robot loop.
 */
void drivetrain_periodic();

void drivetrain_initialize();

void handle_movement(const double* motor_speeds);

void handle_matrix(int ax, int ay, double heading, int controller_rotation);
