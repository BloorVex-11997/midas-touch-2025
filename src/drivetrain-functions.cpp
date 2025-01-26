#include "globals.h"
#include "robot/drivetrain-functions.hpp"
#include "robot/holonomic-calculator.hpp"
#include "robot/debug-utils.h"
#include "utils.h"

// Motor objects
pros::Motor motor1(DRIVETRAIN_PORT_1);
pros::Motor motor2(DRIVETRAIN_PORT_2);
pros::Motor motor3(DRIVETRAIN_PORT_3);

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

void turn() {
    motor1.move(12);
    motor2.move(12);
    motor3.move(12);
}

void halt_movement(){
    motor1.move(0);
    motor2.move(0);
    motor3.move(0);
    motor1.brake();
    motor2.brake();
    motor3.brake();
}