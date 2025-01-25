#pragma once
#include "main.h"

/**
 * calculates the movement for the 3 motors on the Holonomic drive train
 */
void handleMovement(int ax, int ay, double omega);

void haltMovement();