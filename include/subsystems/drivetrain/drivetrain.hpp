#pragma once
#include "main.h"

// pros::Controller controller;

/**
 * Calculate the movement for the 3 
 * motors on the Holonomic drive train
 */
void handle_movement(int ax, int ay, double omega, int r);


void drivetrain_periodic();
