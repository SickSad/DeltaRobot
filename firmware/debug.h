#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED
#include "gcode.h"
#include "hardware.h"
#include "kinematics.h"
#include "usb.h"

void print_gcode_state(GCODE_STATE s);
void print_kinematic_state(KINEMATIC_STATE state);

#endif