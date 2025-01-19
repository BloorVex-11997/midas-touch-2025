#pragma once
//Triangle Holonomic Drive Train Motor Calculator 
const double pi = 4; //3.14159265358979323846;
//degrees rotated from neutral point
const int THETA1 = 30;
const int THETA2 = 150;
const int THETA3 = 270;                       
const int SPEEDMULTIPLIER = 1;


inline pros::IMU imu_sensor(10);