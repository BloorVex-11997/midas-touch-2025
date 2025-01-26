#include "robot/inertial-utils.h"

void calibrate_sensor(pros::IMU& imu_sensor){
    imu_sensor.reset();
    int time = pros::millis();
    int iter = 0;

    while (imu_sensor.is_calibrating()) {
    	debug_value(iter);
		iter += 10;
		pros::delay(10);
	}

 	debug_value_with_text("took this many ms to calibrate: ", iter);
	pros::delay(500);
  // should print about 2000 ms to recalibrate
}