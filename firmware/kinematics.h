#ifndef KINEMATICS_H_INCLUDED
#define KINEMATICS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "hardware.h"

//HEAD CONSTANTS
#define HEAD_P1_X 0.0f
#define HEAD_P1_Y 42.0f
#define HEAD_P2_X 36.3731f
#define HEAD_P2_Y -21.0f
#define HEAD_P3_X -36.3731f
#define HEAD_P3_Y -21.0f
//BODY CONSTANTS
#define BODY_P1_X 0.0f
#define BODY_P1_Y 165.8846f

#define BODY_P2_X 143.6602f
#define BODY_P2_Y -82.9423f

#define BODY_P3_X -143.6602f
#define BODY_P3_Y -82.9423f
//MISC CONSTANTS
#define ROD_LENGTH 245.0f
#define Z_MM_STEP_SIZE ((25.0f * 2.5f) / (200.0f * 8.0f)) //0.0390625f;
#define LINE_STEP_SIZE 0.005f
//#define FEED_RATE_CONSTANT 79872000.0f
#define FEED_RATE_CONSTANT 59872000.0f
#define EXTRUDE_PER_STEP (((3.14159f *16.0f) / (59.0f/11.0f))/(8.0f*200.0f))


typedef struct {    
    float x;
    float y;
    float z; 
    float z1_error;
    float z2_error;
    float z3_error;
    float extrude_length;
    float extrude_error;
    float feed_rate;
} KINEMATIC_STATE;


//void wait(int delay);
void init_kinematic_state(KINEMATIC_STATE *s);
void xyz_to_zzz(float x, float y, float z, float *z1, float *z2, float *z3);
KINEMATIC_STATE line_generator(KINEMATIC_STATE current_state, KINEMATIC_STATE target_state, void (*step_motors)(bool, bool, bool, bool, bool, bool, bool, bool, int));


#endif