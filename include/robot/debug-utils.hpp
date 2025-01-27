#pragma once

#include <string>
#include <cstring>

/**
 * Debug functions used to print values 
 * to the screen, and contains multiple 
 * overloads in case of different values
 */

/**
 * @param text string that prefixes the value
 * @param value the value to be logged
 */
void debug_value_with_text(const std::string& text, double value);

/**
 * @param text string that prefixes the value
 * @param value the value to be logged
 */
void debug_value_with_text(const std::string& text, int value);

/**
 * overload for double.
 * 
 * @param value the value to be logged
 */
void debug_value(double value);

/**
 * overload for int.
 * 
 * @param value the value to be logged
 */
void debug_value(int value);

/**
 * overload for three doubles.
 * 
 * @param line the line on the robot screen
 * @param arg1, arg2, arg3 the values to be logged, in the respective order
 */
void debug_args(int line, double arg1, double arg2, double arg3);

/**
 * overload for three ints.
 * 
 * @param line the line on the robot screen
 * @param arg1, arg2, arg3 the values to be logged, in the respective order
 */
void debug_args(int line, int arg1, int arg2, int arg3);

/**
 * overload for two doubles.
 * 
 * @param line the line on the robot screen
 * @param arg1, arg2 the values to be logged, in the respective order
 */
void debug_args(int line, double arg1, double arg2);

/**
 * overload for two ints.
 * 
 * @param line the line on the robot screen
 * @param arg1, arg2 the values to be logged, in the respective order
 */
void debug_args(int line, int arg1, int arg2);


