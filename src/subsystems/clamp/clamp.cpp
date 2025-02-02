#include "main.h"
#include "clamp.hpp"
#include "globals.hpp"

pros::Motor clamp_motor(CLAMP_PORT);

bool clamp_active = false;
uint32_t command_finish_time = 0;

void set_clamp_voltage(int voltage) {
    clamp_motor.move(voltage);
}

void clamp_periodic() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        clamp_active = !clamp_active;
        command_finish_time = pros::millis() + CLAMP_ACTIVE_DURATION;
    }

    if (pros::millis() <= command_finish_time) {
        set_clamp_voltage(clamp_active ? CLAMP_SPEED : -CLAMP_SPEED);
    }
}