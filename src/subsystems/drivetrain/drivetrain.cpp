#include "globals.hpp"
#include "main.h"
#include "robot/inertial-utils.hpp"
#include "subsystems/drivetrain/drivetrain.hpp"
#include "subsystems/drivetrain/holonomic-calculator.hpp"
#include "robot/debug-utils.hpp"
#include "utils.hpp"

// Motor objects
pros::Motor motor1(DRIVETRAIN_PORT_1);
pros::Motor motor2(DRIVETRAIN_PORT_2);
pros::Motor motor3(DRIVETRAIN_PORT_3);

// pros::Controller controller(pros::E_CONTROLLER_MASTER);

void handle_movement(int ax, int ay, double omega, int r) {

    
    r = clamp(r, -TURN_VOLTAGE_LIMIT, TURN_VOLTAGE_LIMIT);

    update_matrix(omega);
    calculate_motor_values(ax, ay, 0.0);
    const double* motor_value_array = get_motor_values();
    double motor_speeds[3] = {motor_value_array[0], motor_value_array[1], motor_value_array[2]};

    for (int32_t i = 0; i < 3; i++) {
        motor_speeds[i] += r;
        motor_speeds[i] = voltage_clamp(motor_speeds[i]);
    }
    
    debug_args(2, motor_value_array[0], motor_value_array[1], motor_value_array[2]);
    
    motor1.move(static_cast<int32_t>(motor_speeds[0]));
    motor2.move(static_cast<int32_t>(motor_speeds[1]));
    motor3.move(static_cast<int32_t>(motor_speeds[2]));
}



void drivetrain_periodic() {
    int ax = controller.get_analog(ANALOG_RIGHT_X);
	int ay = controller.get_analog(ANALOG_RIGHT_Y);    // Gets amount forward/backward from left joystick
    double heading = 360 - imu_sensor.get_heading();
    int rotation = controller.get_analog(ANALOG_LEFT_X) / 127.0 * TURN_VOLTAGE_LIMIT;
    

    if (DEBUG_MODE){
        debug_args(4, ax, ay, 0);
	    debug_args(5, heading, imu_sensor.get_heading(), 0.0);
    }
	
    handle_movement(ax, ay, heading, rotation);
}