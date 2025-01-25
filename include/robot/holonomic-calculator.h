#pragma once

#include "globals.h"

/*

TODO: documentation 


*/




//returns a pointer to the motorMatrix, ensures that motorMatrix cannot be modified
const double* getMotorValues();

//updates the transformation matrix with the accumulated rotation
void updateMatrix(double omega);
    

//calculates matrix equation for m1,m2,m3
void calculateMotorValues(double ax, double ay, int r);
  

