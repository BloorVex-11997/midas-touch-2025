#pragma once
#include <string>
#include <cstring>

/**
 * Debug functions used to print values 
 * to the screen, and contains multiple 
 * overloads in case of different values
 */


void debug_value_with_text(const std::string& text, double value);

void debug_value_with_text(const std::string& text, int value);

//overload for double
void debug_value(double value);

//overload for int
void debug_value(int value);


//overload for 3 args, double
void debug_args(int line, double arg1, double arg2, double arg3);

//overload for 3 args, int
void debug_args(int line, int arg1, int arg2, int arg3);


//overload for 2 args, double
void debug_args(int line, double arg1, double arg2);

//overload for 2 args, int
void debug_args(int line, int arg1, int arg2);


