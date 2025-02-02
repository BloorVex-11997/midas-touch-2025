#include "subsystems/elevator/elevator.hpp"

#include "globals.hpp"
#include "main.h"
#include "utils.hpp"

pros::Motor elevator_motor_1(ELEVATOR_PORT_1);
pros::Motor elevator_motor_2(ELEVATOR_PORT_2);

bool elevator_active = false;

/**
 * @param voltage [-127, 127]
 */
void set_belt_voltage(int voltage) {
    elevator_motor_1.move(voltage_clamp(-voltage));
    elevator_motor_2.move(voltage_clamp(voltage));
}

void elevator_periodic() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        elevator_active = !elevator_active;
        set_belt_voltage(elevator_active ? BELT_SPEED : 0);
    } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        elevator_active = !elevator_active;
        set_belt_voltage(elevator_active ? -BELT_SPEED : 0);
    }
}
