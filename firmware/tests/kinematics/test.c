#include "../../kinematics.h"
#include <stdio.h>

void print_kinematic_state(KINEMATIC_STATE state){
	printf("Kinematic state\n");
	printf("x: %f\n", state.x);
	printf("y: %f\n", state.y);
	printf("z: %f\n", state.z);
	printf("z1_error: %f\n", state.z1_error);
	printf("z2_error: %f\n", state.z2_error);
	printf("z3_error: %f\n", state.z3_error);
	printf("extrude_length: %f\n", state.extrude_length);
	printf("extrude_error:  %f\n", state.extrude_error);
	printf("feed_rate:      %f\n", state.feed_rate);
}

void debug_step_motors(bool z0_dir, bool z0_step, bool z1_dir, bool z1_step, bool z2_dir, bool z2_step){
	printf("z0: %d %d z1: %d %d z2: %d %d\n", z0_dir, z0_step, z1_dir, z1_step, z2_dir, z2_step);
}


int main (int argc, char **argv){
	float x =10.0f;
	float y =10.0f;
	float z =20.0f;

	float zzz1 =0.0f;
	float zzz2 =0.0f;
	float zzz3 =0.0f;
	
	xyz_to_zzz(x, y, z, &zzz1, &zzz2, &zzz3);
	printf("input- x:%f y:%f z:%f\n", x, y, z);
	printf("output- z1:%f z2:%f z3:%f\n", zzz1, zzz2, zzz3);
	

	KINEMATIC_STATE current;
	init_kinematic_state(&current);
	KINEMATIC_STATE goal;
	init_kinematic_state(&goal);
	
	goal.x = 10.0f;
	goal.y = 10.0f;
	goal.z = 10.0f;

	current = line_generator(current, goal, debug_step_motors);
	print_kinematic_state(current);

	return 1;
}
