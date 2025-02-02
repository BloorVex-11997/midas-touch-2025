#include "clamp.hpp"

#include "globals.hpp"
#include "main.h"

pros::Motor clamp_motor(CLAMP_PORT);

void clamp_initialize() {
    clamp_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
}

bool clamp_active = false;
uint32_t command_finish_time = 0;

void set_clamp_voltage(int voltage) {
    if (voltage == 0) {
        clamp_motor.brake();
    } else {
        clamp_motor.move(voltage);
    }
}

/*
void clamp_periodic() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        clamp_active = !clamp_active;
        command_finish_time = pros::millis() + CLAMP_ACTIVE_DURATION;
    }

    if (pros::millis() <= command_finish_time) {
        set_clamp_voltage(clamp_active ? CLAMP_SPEED : -CLAMP_SPEED);
    }
}
*/

void clamp_periodic() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        set_clamp_voltage(CLAMP_SPEED);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        set_clamp_voltage(-CLAMP_SPEED);
    } else {
        set_clamp_voltage(0);
    }
}