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
void set_elevator_voltage(int voltage) {
    elevator_motor.move(voltage_clamp(voltage));
}

void set_elevator_extension_voltage(int voltage) {
    elevator_extension_motor.move(voltage_clamp(voltage));
}


void elevator_periodic() {

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

    //control for elevator on toggle mode

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        elevator_active = !elevator_active;
        set_elevator_voltage(elevator_active ? 80: 0);
    }
   
    

}