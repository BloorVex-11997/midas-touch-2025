#pragma once 
#include "main.h"
#include "robot/debug-utils.hpp"

/**
	Recalibrates the IMU sensor for the robot, and resets the heading for the robot

	WARNING: If the sensor is recalibrated and its not in the default position the movement will get messed up
	because the heading will have been reset
 */
void calibrate_sensor(pros::IMU& imu_sensor);