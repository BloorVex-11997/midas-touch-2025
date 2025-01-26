#include <cmath>   
#include "robot/holonomic-calculator.hpp"

#define RECIPROCAL_DETERMINANT -2 / (3 * sqrt(2)) // Reciprocal of the determinant
const double initial_omega = 0.0;

/**
 * converts degrees to radians
 */
double rad(double deg){
    return deg * (PI / 180);
}

/**
 * stores motor vector magnitudes
 */
static double motorMatrix[3] = {0.0, 0.0, 0.0};

/**
 * returns a pointer to the motorMatrix, 
 * ensures that motorMatrix cannot be modified
 */
const double* get_motor_values() {
    return motorMatrix; 
}


/**
 * base matrix for calculating motor vectors
 */
static double transformation_matrix[3][3] = {
    // {(-3*cos(rad(initial_omega))/2)+(sqrt(3)*sin(rad(initial_omega))/2),   (sqrt(3)*cos(rad(initial_omega))/2)+((3)*sin(rad(initial_omega))/2),   -1*sqrt(3)/2},
    // {(3*cos(rad(initial_omega))/2)+(sqrt(3)*sin(rad(initial_omega))/2),    (sqrt(3)*cos(rad(initial_omega))/2)-((3)*sin(rad(initial_omega))/2),   -1*sqrt(3)/2},
    // {-1*(sqrt(3)*sin(rad(initial_omega))),                         -1*(sqrt(3)*cos(rad(initial_omega))),                          -1*sqrt(3)/2}
    {(sqrt(3)*cos(rad(initial_omega))/2)+((3)*sin(rad(initial_omega))/2),   (-3*cos(rad(initial_omega))/2)+(sqrt(3)*sin(rad(initial_omega))/2),   -1*sqrt(3)/2},
    {(sqrt(3)*cos(rad(initial_omega))/2)-((3)*sin(rad(initial_omega))/2),    (3*cos(rad(initial_omega))/2)+(sqrt(3)*sin(rad(initial_omega))/2),   -1*sqrt(3)/2},
    {-1*(sqrt(3)*cos(rad(initial_omega))),                         -1*(sqrt(3)*sin(rad(initial_omega))),                          -1*sqrt(3)/2}
};


/**
 * updates the transformation matrix with 
 * the accumulated rotation
 */
void update_matrix(double phi) {
    transformation_matrix[0][0] = (sqrt(3)*cos(rad(phi))/2)+((3)*sin(rad(phi))/2);
    transformation_matrix[0][1] = (-3*cos(rad(phi))/2)+(sqrt(3)*sin(rad(phi))/2);
    transformation_matrix[1][0] = (sqrt(3)*cos(rad(phi))/2)-((3)*sin(rad(phi))/2);
    transformation_matrix[1][1] = (3*cos(rad(phi))/2)+(sqrt(3)*sin(rad(phi))/2);
    transformation_matrix[2][0] = -1*(sqrt(3)*cos(rad(phi)));
    transformation_matrix[2][1] = -1*(sqrt(3)*sin(rad(phi)));
}

/**
 * calculates matrix equation for m1,m2,m3
 */
void calculate_motor_values(double ax, double ay, double r) {
    double componentMatrix[3] = {ax,ay,0.0};
    // For the first row of the result
    motorMatrix[0] = transformation_matrix[0][0] * componentMatrix[0] +
                     transformation_matrix[0][1] * componentMatrix[1] +
                     transformation_matrix[0][2] * componentMatrix[2];

    // For the second row of the result
    motorMatrix[1] = transformation_matrix[1][0] * componentMatrix[0] +
                     transformation_matrix[1][1] * componentMatrix[1] +
                     transformation_matrix[1][2] * componentMatrix[2];

    // For the third row of the result
    motorMatrix[2] = transformation_matrix[2][0] * componentMatrix[0] +
                     transformation_matrix[2][1] * componentMatrix[1] +
                     transformation_matrix[2][2] * componentMatrix[2];

    motorMatrix[0] *= RECIPROCAL_DETERMINANT;
    motorMatrix[1] *= RECIPROCAL_DETERMINANT;
    motorMatrix[2] *= RECIPROCAL_DETERMINANT;
}
