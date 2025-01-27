#include <cmath>   
#include "utils.hpp"
#include "subsystems/drivetrain/holonomic-calculator.hpp"

const double RECIPROCAL_DETERMINANT = 2 / (3 * sqrt(3)); // Reciprocal of the determinant
const double INITIAL_OMEGA = 0.0;

/**
 * For more documentation, 
 * @see include/subsystems/drivetrain/holonomic-calculator.hpp
 */

/**
 * converts degrees to radians
 */
double rad(double deg){
    return deg * (PI / 180);
}

/**
 * stores motor vector magnitudes
 */
static double motor_matrix[3] = {0.0, 0.0, 0.0};

/**
 * returns a pointer to the motor_matrix, 
 * ensures that motor_matrix cannot be modified
 */
const double* get_motor_values() {
    return motor_matrix; 
}

/**
 * @param rotation the voltage applied equally to each wheel for rotation.
 */
void apply_controller_rotation(int rotation) {
    rotation = clamp(rotation, -TURN_VOLTAGE_LIMIT, TURN_VOLTAGE_LIMIT);
    
    for (int i = 0; i < 3; i++) {
        motor_matrix[i] += rotation;
    }
}


/**
 * 
 */

void clamp_motor_values() {
    for (int32_t i = 0; i < 3; i++) {
        motor_matrix[i] = voltage_clamp(motor_matrix[i]);
    }
}

/**
 * base matrix for calculating motor vectors
 */
static double transformation_matrix[3][3] = {
    {(-3*sin(rad(INITIAL_OMEGA))/2)-(sqrt(3)*cos(rad(INITIAL_OMEGA))/2),   (3*cos(rad(INITIAL_OMEGA))/2)-(sqrt(3)*sin(rad(INITIAL_OMEGA))/2),   sqrt(3)/2},
    {(3*sin(rad(INITIAL_OMEGA))/2)-(sqrt(3)*cos(rad(INITIAL_OMEGA))/2),    (-3*cos(rad(INITIAL_OMEGA))/2)-(sqrt(3)*sin(rad(INITIAL_OMEGA))/2),   sqrt(3)/2},
    {(sqrt(3)*cos(rad(INITIAL_OMEGA))),                         (sqrt(3)*sin(rad(INITIAL_OMEGA))),                          sqrt(3)/2}
};


/**
 * updates the transformation matrix with 
 * the accumulated rotation
 */
void update_matrix_omega(double omega) {
    transformation_matrix[0][0] = (-3*sin(rad(omega))/2)-(sqrt(3)*cos(rad(omega))/2);
    transformation_matrix[0][1] = (3*cos(rad(omega))/2)-(sqrt(3)*sin(rad(omega))/2);
    transformation_matrix[1][0] = (3*sin(rad(omega))/2)-(sqrt(3)*cos(rad(omega))/2);
    transformation_matrix[1][1] = (-3*cos(rad(omega))/2)-(sqrt(3)*sin(rad(omega))/2);
    transformation_matrix[2][0] = (sqrt(3)*cos(rad(omega)));
    transformation_matrix[2][1] = (sqrt(3)*sin(rad(omega)));
}

/**
 * calculates matrix equation for m1,m2,m3
 */
void calculate_motor_values(double ax, double ay, double r) {
    double componentMatrix[3] = {ax, ay, r};
    // For the first row of the result
    motor_matrix[0] = transformation_matrix[0][0] * componentMatrix[0] +
                     transformation_matrix[0][1] * componentMatrix[1] +
                     transformation_matrix[0][2] * componentMatrix[2];

    // For the second row of the result
    motor_matrix[1] = transformation_matrix[1][0] * componentMatrix[0] +
                     transformation_matrix[1][1] * componentMatrix[1] +
                     transformation_matrix[1][2] * componentMatrix[2];

    // For the third row of the result
    motor_matrix[2] = transformation_matrix[2][0] * componentMatrix[0] +
                     transformation_matrix[2][1] * componentMatrix[1] +
                     transformation_matrix[2][2] * componentMatrix[2];

    motor_matrix[0] *= RECIPROCAL_DETERMINANT;
    motor_matrix[1] *= RECIPROCAL_DETERMINANT;
    motor_matrix[2] *= RECIPROCAL_DETERMINANT;
}
