#include "utils.hpp"
#include "globals.hpp"

/**
 * For documentation, 
 * @see include/utils.hpp
 */

int clamp(int x, int min, int max) {
    if (x > max)
        return max;
    else if (x < min)
        return min;
    else return x;
}

int voltage_clamp(int voltage) {
    return clamp(voltage, -ABS_VOLTAGE_LIMIT, ABS_VOLTAGE_LIMIT);
}

int sign(double x) {
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    else
        return 1;
}