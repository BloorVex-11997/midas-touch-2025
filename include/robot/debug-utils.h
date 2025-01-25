#pragma once
#include <string>
#include <cstring>

/**
 * different debug functions used to print values to the screen, and contains multiple overloads in case of different values
 */
void debug_value(double value);

void debug_value(int value);

void debug_value_with_text(const std::string& text, double value);

void debug_value_with_text(const std::string& text, int value);

void debug_args(int line, double arg1, double arg2, double arg3);