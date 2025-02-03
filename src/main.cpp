#include "main.h"

#include "robot/inertial-utils.hpp"
#include "subsystems/clamp/clamp.hpp"
#include "subsystems/claw/claw.hpp"
#include "subsystems/drivetrain/drivetrain.hpp"
#include "subsystems/drivetrain/holonomic-calculator.hpp"
#include "subsystems/elevator/elevator.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
    static bool pressed = false;
    pressed = !pressed;
    if (pressed) {
        pros::lcd::set_text(2, "I was pressed!");
    } else {
        pros::lcd::clear_line(2);
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    // initialize all robot objects

    // pros::lcd::initialize();
    // pros::lcd::set_text(1, "Hello PROS User!");

    // pros::lcd::register_btn1_cb(on_center_button);

    // calibrate_sensor(imu_sensor);

    clamp_initialize();
    drivetrain_initialize();
    autonomous();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    pros::lcd::initialize();
    calibrate_sensor(imu_sensor);
    clamp_initialize();
    drivetrain_initialize();
}

/**
 * The main loop that handles all robot functions
 * and synchronously calls all subsystem periodic functions.
 * Runs approximately every 20 ms (50 iterations per second)
 */
void mainloop() {
    while (true) {
        drivetrain_periodic();
        // claw_periodic();
        elevator_periodic();
        clamp_periodic();

        pros::delay(20);  // delay for 20 ms
    }
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    // uint32_t start = pros::millis();
    // uint32_t end = start + AUTO_DURATION;
    // while (true) {
    //     double heading = 360 - imu_sensor.get_heading();

    //     const int forward = pros::millis() <= end ? 50 : 0;
    //     debug_value_with_text("Forward: ", forward);
    //     debug_value_with_text("End: ", (int)end);

    //     // update the motor values
    //     handle_matrix(0, forward, heading, 0);

    //     // use motor values to move
    //     handle_movement(get_motor_values());
    //     pros::delay(20);
    // }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    mainloop();
}