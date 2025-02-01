#include "main.h"
#include "globals.hpp"
#include "utils.hpp"
#include "subsystems/elevator/elevator.hpp"

pros::Motor elevator_motor(ELEVATOR_PORT);
pros::Motor elevator_extension_motor(ELEVATOR_EXTENSION_PORT);

bool elevator_active = false;




/**
 * @param voltage [-127, 127]
 */
void set_belt_voltage(int voltage) {
    elevator_motor.move(voltage_clamp(voltage));
}


void elevator_periodic() {

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        elevator_active = !elevator_active;
        set_belt_voltage(elevator_active ? -80: 0);
    }
}
