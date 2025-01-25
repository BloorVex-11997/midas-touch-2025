#include "globals.h"
#include "robot/drivetrain-functions.h"
#include "robot/holonomic-calculator.h"
#include "robot/debug-utils.h"

//robot objects
pros::Motor motor1(12);
pros::Motor motor2(20);
pros::Motor motor3(1);

void handleMovement(int ax, int ay, double omega){
    updateMatrix(omega);
    calculateMotorValues(ax,ay,0);
    const double* motorValueArray = getMotorValues();
    
    debug_args(2, motorValueArray[0], motorValueArray[1], motorValueArray[2]);
    
    motor1.move(static_cast<int>(motorValueArray[0]));
    motor2.move(static_cast<int>(motorValueArray[1]));
    motor3.move(static_cast<int>(motorValueArray[2]));
}

void haltMovement(){
    motor1.move(0);
    motor2.move(0);
    motor3.move(0);
    motor1.brake();
    motor2.brake();
    motor3.brake();
}