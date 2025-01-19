#pragma once
#include <cmath>   
#include "globals.h"
#include "utils.h"

/*

Equation (in degrees) ->

|m1|    | cos(theta1 + 90)   sin(theta1 + 90)    1 |   |ax|
|m2| =  | cos(theta2 + 90)   sin(theta2 + 90)    1 | * |ay|
|m3|    | cos(theta3 + 90)   sin(theta3 + 90)    1 |   |r |

where theta_i represents the angle of a motor_i with respect
to a line drawn through the centroid of the three wheels 

omega is the accumulated rotation of the robot with respect to
how much the front has rotated from its neutral position

theta1 = 30 + omega
theta2 = 150 + omega 
theta3 = 270 + omega 

a is the vector representing the movement of the robot
by extension ax and ay are the x and y components of the vector a

r is the angular speed of the wheels 
*/


//stores motor vector magnitudes
static double motorMatrix[3] = {0.0, 0.0, 0.0};

//returns a pointer to the motorMatrix, ensures that motorMatrix cannot be modified
const double* getMotorValues(){
    return motorMatrix; 
}


//base matrix for calculating motor vectors
static double TransformationMatrix[3][3] = {
    {cos(rad(THETA1 + 90.0)), sin(rad(THETA1 + 90.0)), 1},
    {cos(rad(THETA2 + 90.0)), sin(rad(THETA2 + 90.0)), 1},
    {cos(rad(THETA3 + 90.0)), sin(rad(THETA3 + 90.0)), 1}
};


//updates the transformation matrix with the accumulated rotation
void updateMatrix(double omega)
    {
    TransformationMatrix[0][0] = cos(rad(THETA1 + 90.0 + omega));
    TransformationMatrix[0][1] = sin(rad(THETA1 + 90.0 + omega));
    TransformationMatrix[1][0] = cos(rad(THETA2 + 90.0 + omega));
    TransformationMatrix[1][1] = sin(rad(THETA2 + 90.0 + omega));
    TransformationMatrix[2][0] = cos(rad(omega));
    TransformationMatrix[2][1] = sin(rad(omega));
    }

//calculates matrix equation for m1,m2,m3
void calculateMotorValues(double ax, double ay, int r)
    {
    
    
    int componentMatrix[3] = {ax,ay,r};

    //For the first row of the result
    motorMatrix[0] = TransformationMatrix[0][0] * componentMatrix[0] +
                     TransformationMatrix[0][1] * componentMatrix[1] +
                     TransformationMatrix[0][2] * componentMatrix[2];

    // For the second row of the result
    motorMatrix[1] = TransformationMatrix[1][0] * componentMatrix[0] +
                     TransformationMatrix[1][1] * componentMatrix[1] +
                     TransformationMatrix[1][2] * componentMatrix[2];

    // For the third row of the result
    motorMatrix[2] = TransformationMatrix[2][0] * componentMatrix[0] +
                     TransformationMatrix[2][1] * componentMatrix[1] +
                     TransformationMatrix[2][2] * componentMatrix[2];
    }

