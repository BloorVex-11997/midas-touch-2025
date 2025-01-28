#pragma once

#include "globals.hpp"

/**
 *  IMPORTANT: consult read me section for more in depth description on how the math works/is derived
*/


/**
 * @return const double[3] - motor_matrix containing the speed values for each motor
 */
const double* get_motor_values();

/**
 * Apply a voltage rotation to each of the wheels in the motor
 * matrix to reorient the robot.
 * 
 * Clamps rotation to the range [-TURN_VOLTAGE_LIMIT, TURN_VOLTAGE_LIMIT]
 * @see globals.h for TURN_VOLTAGE_LIMIT
 * 
 * @param rotation the voltage applied equally to each wheel for rotation.
 */
void apply_controller_rotation(int rotation);


/**
 * Clamp each of the motor values in the appropriate range.
 * 
 * @see utils.h for voltage_clamp()
 */
void clamp_motor_values();

/**
 * Update transformation matrix with the current
 * field-relative orientation of the robot.
 * 
 * @param omega the field-relative orientation of the robot.
 *              Retrieved from the IMU sensor.
 */
void update_matrix_omega(double omega);
    

/**
 * Calculate the voltages for each of the motors
 * given an desired direction and save voltage values 
 * in motor_matrix.
 * 
 * @param ax the horizontal component of the direction vector
 * @param ay the vertical component of the direction vector.
 * @param r magic number that is always zero.
 */
void calculate_motor_values(double ax, double ay, double r);
  

