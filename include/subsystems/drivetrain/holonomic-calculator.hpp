#pragma once
#include "globals.hpp"

/*
TODO: documentation 
*/

/**
 * returns a pointer to the motorMatrix, 
 * ensures that motorMatrix cannot be modified
 */
const double* get_motor_values();

/**
 * updates the transformation matrix with
 * the accumulated rotation
 */
void update_matrix(double omega);
    

/**
 * calculates matrix equation for m1,m2,m3
 */
void calculate_motor_values(double ax, double ay, double r);
  

