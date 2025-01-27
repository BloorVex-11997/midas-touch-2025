#pragma once

/**
 * Clamp x in the range [min, max]
 * @param x the value to be clamped
 * @param min the minimum value
 * @param max the maximum value
 * @return clamped x
 */
int clamp(int x, int min, int max);

/**
 * Clamp voltage in the voltage range defined
 * by [-ABS_VOLTAGE_LIMIT, ABS_VOLTAGE_LIMIT]
 * @see globals.h for ABS_VOLTAGE_LIMIT
 * @param voltage the voltage to be clamped
 * @returns clamped voltage
 */
int voltage_clamp(int voltage);