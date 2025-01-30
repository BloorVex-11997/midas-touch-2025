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


    
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        //elevator_active = !elevator_active;

        set_elevator_extension_voltage(100);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        //elevator_active = !elevator_active;

        set_elevator_extension_voltage(-100);
    }
    else{
        set_elevator_extension_voltage(0);
    }


    //control for elevator 
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        //elevator_active = !elevator_active;

        set_elevator_voltage(127);
    }
   
    else{
         set_elevator_voltage(0);
    }


}