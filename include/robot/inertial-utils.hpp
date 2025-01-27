#pragma once

#include "main.h"
#include "robot/debug-utils.hpp"

/**
	Recalibrate the IMU sensor, resetting the 
	robot's heading.

	@warning The robot must be in the default position before calibration.
				Otherwise, movement will be scuffed.
	
	@param imu_sensor the sensor that should be calibrated.
 */
void calibrate_sensor(pros::IMU& imu_sensor);