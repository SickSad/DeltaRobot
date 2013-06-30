#include "kinematics.h"

void init_kinematic_state(KINEMATIC_STATE *s){
    (*s).x = 0.0f;
    (*s).y = 0.0f;
    (*s).z = 0.0f;
    (*s).z1_error = 0.0f;
    (*s).z2_error = 0.0f;
    (*s).z3_error = 0.0f;
    (*s).extrude_length = 0.0f;
    (*s).extrude_error = 0.0f;
    (*s).feed_rate = 0.0f;
}

void xyz_to_zzz(float x, float y, float z, float *z1, float *z2, float *z3){
    *z1 = sqrtf(powf(ROD_LENGTH, 2) - powf(BODY_P1_X - HEAD_P1_X -x, 2) - powf(BODY_P1_Y - HEAD_P1_Y - y, 2)) - z;
    *z2 = sqrtf(powf(ROD_LENGTH, 2) - powf(BODY_P2_X - HEAD_P2_X -x, 2) - powf(BODY_P2_Y - HEAD_P2_Y - y, 2)) - z;
    *z3 = sqrtf(powf(ROD_LENGTH, 2) - powf(BODY_P3_X - HEAD_P3_X -x, 2) - powf(BODY_P3_Y - HEAD_P3_Y - y, 2)) - z;
}

KINEMATIC_STATE line_generator(KINEMATIC_STATE current_state, KINEMATIC_STATE target_state, void (*step_motors)(bool, bool, bool, bool, bool, bool, bool, bool, int) ){

    float x1 = current_state.x;
    float y1 = current_state.y;
    float z1 = current_state.z;
    float x2 = target_state.x;
    float y2 = target_state.y;
    float z2 = target_state.z;

    float feed_rate_1 = current_state.feed_rate;
    float feed_rate_2 = target_state.feed_rate;

    float e1 = current_state.extrude_length;
    float e2 = target_state.extrude_length;


    float z1_error = current_state.z1_error;
    float z2_error = current_state.z2_error;
    float z3_error = current_state.z3_error;

    //motor control booleans
    bool z1_dir = false;
    bool z2_dir = false;
    bool z3_dir = false;
    bool e_dir =false;

    bool z1_step = false;
    bool z3_step = false;
    bool z2_step = false;
    bool e_step =false;


    //calulation values
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float e = current_state.extrude_error;
    float zzz1 = 0.0f;
    float zzz3 = 0.0f;
    float zzz2 = 0.0f;
    float prev_zzz1 = 0.0f;
    float prev_zzz3 = 0.0f;
    float prev_zzz2 = 0.0f;
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float delta_z = z2 - z1;
    float delta_e = e2 - e1;
    float ratio = 0.0f;
    float distance = sqrtf(powf(delta_x,2) + powf(delta_y,2) + powf(delta_z,2));

    int num_steps = (int)((distance / LINE_STEP_SIZE) + 0.5f); //add 0.5 so the number is rounded rather than truncated when converted to int 

    if (feed_rate_1 == 0.0f){
        feed_rate_1 = 9000.0f;
    }
    int current_delay = (int)((float)Z_MM_STEP_SIZE / ((float)feed_rate_1/(float)FEED_RATE_CONSTANT));
    int target_delay = (int)((float)Z_MM_STEP_SIZE / ((float)feed_rate_2/(float)FEED_RATE_CONSTANT));
    float delay = (float)current_delay;
    float delay_delta = (float)target_delay - (float)current_delay;
    float delay_step = 0;
    //int current_delay = 400;

    

    //set the previous value to the start point
    xyz_to_zzz(x1, y1, z1, &prev_zzz1, &prev_zzz2, &prev_zzz3);

    float num_extrude_steps = (delta_e/EXTRUDE_PER_STEP);
    float extrude_steps_per_itter  =0;

    if (num_steps > 0){
        extrude_steps_per_itter = num_extrude_steps / (float)num_steps;
        delay_step = delay_delta/(float)num_steps;
    }else{
        extrude_steps_per_itter = 0;
    }


    char debug_buffer[128];
    sprintf(debug_buffer,"\tDELAY: %f\n", delay);
    write_serial(debug_buffer);
    sprintf(debug_buffer,"\tDELAY DELTA: %f\n", delay_delta);
    write_serial(debug_buffer);
    sprintf(debug_buffer,"\tDELAY STEP: %f\n", delay_step);
    write_serial(debug_buffer);


    int step = 0;
    for(step = 0; step < num_steps; step++){
        delay += delay_step;

        ratio = ((float)step + 1) / ((float)num_steps);

        x = x1 + ratio * delta_x;
        y = y1 + ratio * delta_y;
        z = z1 + ratio * delta_z;
        xyz_to_zzz(x, y, z, &zzz1, &zzz2, &zzz3);
        z1_error += prev_zzz1 - zzz1;
        z2_error += prev_zzz2 - zzz2;
        z3_error += prev_zzz3 - zzz3;

        e += extrude_steps_per_itter;
        if (e > 1.0f){
            e_dir = true;
            e_step = true;
            e = e - 1.0f;
        }else if(e < -1.0f){
            e_dir = false;
            e_step = true;
            e = e + 1.0f;
        }else{
            e_step = false;
        }


        if(z1_error >= Z_MM_STEP_SIZE){
            //step forward
            z1_error = z1_error - Z_MM_STEP_SIZE;
            z1_dir = false;
            z1_step = true;
        } 
        else if(z1_error <= -Z_MM_STEP_SIZE){
            //step backward
            z1_error = z1_error + Z_MM_STEP_SIZE;
            z1_dir = true;
            z1_step = true;
        }
        else{
        	z1_step = false;
        }

        if(z2_error >= Z_MM_STEP_SIZE){
            //step forward
            z2_error = z2_error - Z_MM_STEP_SIZE;
            z2_dir = false;
            z2_step = true;
        } 
        else if(z2_error <= -Z_MM_STEP_SIZE){
            //step backward
            z2_error = z2_error + Z_MM_STEP_SIZE;
            z2_dir = true;
            z2_step = true;
        }
        else{
        	z2_step = false;
        }

        if(z3_error >= Z_MM_STEP_SIZE){
            //step forward
            z3_error = z3_error - Z_MM_STEP_SIZE;
            z3_dir = false;
            z3_step = true;
        } 
        else if(z3_error <= -Z_MM_STEP_SIZE){
            //step backward
            z3_error = z3_error + Z_MM_STEP_SIZE;
            z3_dir = true;
            z3_step = true;
        }
        else{
        	z3_step = false;
        }

        step_motors(z1_dir, z1_step, z2_dir, z2_step, z3_dir, z3_step, e_dir, e_step, (int)delay);
        prev_zzz1 = zzz1;
        prev_zzz2 = zzz2;
        prev_zzz3 = zzz3;
        z1_step = false;
        z2_step = false;
        z3_step = false;
    }

    target_state.z1_error = z1_error;
    target_state.z2_error = z2_error;
    target_state.z3_error = z3_error;
    
    //if e gets broken, clear it otherwise extrusion will be messed up on next run
    if (e > 1.0f) e =0.0f;
    if (e < 1.0f) e =0.0f;
    target_state.extrude_error = e;

    return target_state;
}