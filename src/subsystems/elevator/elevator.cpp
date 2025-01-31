#include "main.h"
#include "globals.hpp"
#include "utils.hpp"
#include "subsystems/elevator/elevator.hpp"

pros::Motor elevator_motor(ELEVATOR_PORT);
pros::Motor elevator_extension_motor(ELEVATOR_EXTENSION_PORT);

bool elevator_active = false;
int extension_end_time = 0; // the time at which the extension should stop
bool extension_direction = false; // true -> extend, otherwise retract

void set_extension_voltage(int voltage) {
    voltage = extension_direction ? -1 * voltage : voltage;
    elevator_extension_motor.move(voltage);
}

void extend_elevator() {
    extension_direction = true;
    extension_end_time = pros::millis() + ELEVATOR_EXTENSION_DURATION;
}

void retract_elevator() {
    extension_direction = false;
    extension_end_time = pros::millis() + ELEVATOR_EXTENSION_DURATION;
}

/**
 * @param voltage [-127, 127]
 */
void set_belt_voltage(int voltage) {
    elevator_motor.move(voltage_clamp(voltage));
}

void set_elevator_extension_voltage(int voltage) {
    elevator_extension_motor.move(voltage_clamp(voltage));
}


void elevator_periodic() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        if (extension_direction)
            retract_elevator();
        else
            extend_elevator();
    }

    if (pros::millis() <= extension_end_time) {
        set_extension_voltage(127);
    } else {
        set_extension_voltage(0);
    //makes sure you can't move arm and spin at the same time 
    if (!elevator_active){

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            //elevator_active = !elevator_active;

            set_elevator_extension_voltage(60);
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            //elevator_active = !elevator_active;

            set_elevator_extension_voltage(60);
        }
        else{
            set_elevator_extension_voltage(0);
        }
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        elevator_active = !elevator_active;
        set_belt_voltage(elevator_active ? 80: 0);
    }
}