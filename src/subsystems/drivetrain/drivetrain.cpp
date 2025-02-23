#include "subsystems/drivetrain/drivetrain.hpp"

#include "globals.hpp"
#include "main.h"
#include "robot/debug-utils.hpp"
#include "robot/inertial-utils.hpp"
#include "subsystems/drivetrain/holonomic-calculator.hpp"
#include "utils.hpp"

// Motor objects
pros::Motor motor1(DRIVETRAIN_PORT_1);
pros::Motor motor2(DRIVETRAIN_PORT_2);
pros::Motor motor3(DRIVETRAIN_PORT_3);

bool is_precision_drive = false;

void drivetrain_initialize() {
    motor1.set_brake_mode(MOTOR_BRAKE_HOLD);
    motor2.set_brake_mode(MOTOR_BRAKE_HOLD);
    motor3.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/**
 * Apply the motor_speeds to each of the motors.
 *
 * @param motor_speeds const double[3] - values for each of
 *                      the three motors.
 */
void handle_movement(const double* motor_speeds) {
    if (DEBUG_MODE) debug_args(2, motor_speeds[0], motor_speeds[1], motor_speeds[2]);

    double multiplier = 2.0;

    if (is_precision_drive) {
        multiplier = PRECISION_MULTIPLIER;
    }

    int speed1 = clamp(static_cast<int32_t>(motor_speeds[0] * multiplier), -ABS_VOLTAGE_LIMIT, ABS_VOLTAGE_LIMIT);
    int speed2 = clamp(static_cast<int32_t>(motor_speeds[1] * multiplier), -ABS_VOLTAGE_LIMIT, ABS_VOLTAGE_LIMIT);
    int speed3 = clamp(static_cast<int32_t>(motor_speeds[2] * multiplier), -ABS_VOLTAGE_LIMIT, ABS_VOLTAGE_LIMIT);

    motor1.move(speed1);
    motor2.move(speed2);
    motor3.move(speed3);

    if (speed1 == 0) {
        motor1.brake();
    }
    if (speed2 == 0) {
        motor2.brake();
    }
    if (speed3 == 0) {
        motor3.brake();
    }
}

/**
 * Update the motor_matrix with new information
 * such as the desired direction vector, heading,
 * and desired rotation.
 *
 * @param ax the horizontal component of the direction vector.
 * @param ay the vertical component of the direction vector.
 * @param heading the current field-relative heading of the robot.
 * @param controller_rotation the desired amount rotation for the robot.
 */
void handle_matrix(int ax, int ay, double heading, int controller_rotation) {
    // updates matrix with accumulated rotation
    update_matrix_omega(heading);

    // calculates the matrix with the new accumulated rotation
    calculate_motor_values(ax, ay, 0.0);

    // applies the rotation from the controller
    apply_controller_rotation(controller_rotation);

    // clamp motor the values to [-127, 127] after applying rotation
    clamp_motor_values();
}

/**
 * @see include/subsystems/drivetrain/drivetrain.hpp
 */
void drivetrain_periodic() {
    // read all inputs
    int ax = controller.get_analog(ANALOG_RIGHT_X);
    int ay = controller.get_analog(ANALOG_RIGHT_Y);  // Gets amount forward/backward from left joystick

    double heading = 360 - imu_sensor.get_heading();
    int controller_rotation = controller.get_analog(ANALOG_LEFT_X) / 127.0 * TURN_VOLTAGE_LIMIT;

    // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
    if (false) {
        calibrate_sensor(imu_sensor);
    }

    is_precision_drive = static_cast<bool>(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));

    if (DEBUG_MODE) {
        debug_args(4, ax, ay, 0);
        debug_args(5, heading, imu_sensor.get_heading(), 0.0);
    }

    // update the motor values
    handle_matrix(ax, ay, heading, controller_rotation);

    // use motor values to move
    handle_movement(get_motor_values());
}