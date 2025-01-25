
#include <cmath>   
#include "robot/holonomic-calculator.h"

//converts degrees to radians
double rad(double deg){
    return deg * (pi / 180);
}



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
    TransformationMatrix[2][0] = cos(rad(THETA3 + 90.0 + omega));
    TransformationMatrix[2][1] = sin(rad(THETA3 + 90.0 + omega));
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

