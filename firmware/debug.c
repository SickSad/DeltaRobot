#include "debug.h"

void print_gcode_state(GCODE_STATE s){
	char debug_buffer[128];
	sprintf(debug_buffer,"GCODE STATE\n");
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\traw_string: %s\n", s.raw_string);
	write_serial(debug_buffer);

	sprintf(debug_buffer,"\tcalculated_checksum: %d\n", s.calculated_checksum);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tline_number: %d\n", s.line_number);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tline_number_set: %hhu\n", s.line_number_set);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tchecksum: %d\n", s.checksum);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tchecksum_set: %hhu\n", s.checksum_set);
	write_serial(debug_buffer);
    
    sprintf(debug_buffer,"\tx: %f\n", s.x);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tx_set: %hhu\n", s.x_set);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\ty: %f\n", s.y);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\ty_set: %hhu\n", s.y_set);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tz: %f\n", s.z);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tz_set: %hhu\n", s.z_set);
	write_serial(debug_buffer);
    
    sprintf(debug_buffer,"\textrude_length: %f\n", s.extrude_length);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\textrude_length_set: %hhu\n", s.extrude_length_set);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tfeed_rate: %f\n", s.feed_rate);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tfeed_rate_set: %hhu\n", s.feed_rate_set);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\ttool_number: %f\n", s.tool_number);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\ttool_number_set: %hhu\n", s.tool_number_set);
    write_serial(debug_buffer);

    sprintf(debug_buffer,"\tg_command: %f\n", s.g_command);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tg_command_set: %hhu\n", s.g_command_set);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tm_command: %f\n", s.m_command);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tm_command_set: %hhu\n", s.m_command_set);
	write_serial(debug_buffer);

    sprintf(debug_buffer,"\ts_parameter: %f\n", s.s_parameter);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\ts_parameter_set: %hhu\n", s.s_parameter_set);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tp_parameter: %f\n", s.p_parameter);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tp_parameter_set: %hhu\n", s.p_parameter_set);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tr_parameter: %f\n", s.r_parameter);
	write_serial(debug_buffer);
    sprintf(debug_buffer,"\tr_parameter_set: %hhu\n", s.r_parameter_set);
	write_serial(debug_buffer);

	sprintf(debug_buffer,"\tx_offset: %f\n", s.x_offset);
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\ty_offset: %f\n", s.y_offset);
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\tz_offset: %f\n", s.z_offset);
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\textrude_offset: %f\n", s.extrude_offset);
	write_serial(debug_buffer);
}

void print_kinematic_state(KINEMATIC_STATE state){
	char debug_buffer[128];
	sprintf(debug_buffer,"KINEMATIC STATE\n");
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\tx: %f\n", state.x);
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\ty: %f\n", state.y);
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\tz: %f\n", state.z);
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\tz1_error: %f\n", state.z1_error);
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\tz2_error: %f\n", state.z2_error);
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\tz3_error: %f\n", state.z3_error);
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\textrude_length: %f\n", state.extrude_length);
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\textrude_error:  %f\n", state.extrude_error);
	write_serial(debug_buffer);
	sprintf(debug_buffer,"\tfeed_rate:      %f\n", state.feed_rate);
	write_serial(debug_buffer);
}