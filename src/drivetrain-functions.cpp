#include "globals.h"
#include "robot/drivetrain-functions.hpp"
#include "robot/holonomic-calculator.hpp"
#include "robot/debug-utils.h"

// Motor objects
pros::Motor motor1(DRIVETRAIN_PORT_1);
pros::Motor motor2(DRIVETRAIN_PORT_2);
pros::Motor motor3(DRIVETRAIN_PORT_3);

void handle_movement(int ax, int ay, double omega){
    update_matrix(omega);
    calculate_motor_values(ax, ay, 0.0);
    const double* motorValueArray = get_motor_values();
    
    debug_args(2, motorValueArray[0], motorValueArray[1], motorValueArray[2]);
    
    motor1.move(static_cast<int32_t>(motorValueArray[0]));
    motor2.move(static_cast<int32_t>(motorValueArray[1]));
    motor3.move(static_cast<int32_t>(motorValueArray[2]));
}

void halt_movement(){
    motor1.move(0);
    motor2.move(0);
    motor3.move(0);
    motor1.brake();
    motor2.brake();
    motor3.brake();
}