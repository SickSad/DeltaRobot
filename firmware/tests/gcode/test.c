#include "../../gcode.h"
#include <stdio.h>


void print_state(GCODE_STATE s){
    printf("\tcalculated_checksum: %d\n", s.calculated_checksum);
    printf("\tline_number: %d\n", s.line_number);
    printf("\tline_number_set: %hhu\n", s.line_number_set);
    printf("\tchecksum: %d\n", s.checksum);
    printf("\tchecksum_set: %hhu\n", s.checksum_set);
    
    printf("\tx: %f\n", s.x);
    printf("\tx_set: %hhu\n", s.x_set);
    printf("\ty: %f\n", s.y);
    printf("\ty_set: %hhu\n", s.y_set);
    printf("\tz: %f\n", s.z);
    printf("\tz_set: %hhu\n", s.z_set);
    
    printf("\textrude_length: %f\n", s.extrude_length);
    printf("\textrude_length_set: %hhu\n", s.extrude_length_set);
    printf("\tfeed_rate: %f\n", s.feed_rate);
    printf("\tfeed_rate_set: %hhu\n", s.feed_rate_set);
    printf("\ttool_number: %f\n", s.tool_number);
    printf("\ttool_number_set: %hhu\n", s.tool_number_set);
    
    printf("\tg_command: %f\n", s.g_command);
    printf("\tg_command_set: %hhu\n", s.g_command_set);
    printf("\tm_command: %f\n", s.m_command);
    printf("\tm_command_set: %hhu\n", s.m_command_set);

    printf("\ts_parameter: %f\n", s.s_parameter);
    printf("\ts_parameter_set: %hhu\n", s.s_parameter_set);
    printf("\tp_parameter: %f\n", s.p_parameter);
    printf("\tp_parameter_set: %hhu\n", s.p_parameter_set);
    printf("\tr_parameter: %f\n", s.r_parameter);
    printf("\tr_parameter_set: %hhu\n", s.r_parameter_set);
}

int main (int argc, char **argv)
{
    FILE * gcodeFile;
    char lineBuffer[1024];
    char * lineBufferPointer = &lineBuffer[0];
    GCODE_STATE previous_command; //stores the previous gcode command
    GCODE_STATE current_command; //stores the next gcode command
    init_gcode_state(&previous_command);
    init_gcode_state(&current_command);

    gcodeFile = fopen("test.gcode","r");
    if(gcodeFile == NULL){
        printf("Error: file dosen't exist");
        return -1;
    }

    printf ("GCode interpreter test\n");
    while(fgets(lineBuffer, 1024, gcodeFile) != NULL){
        //reset the line buffer pointer to the start of the line
        lineBufferPointer = &lineBuffer[0]; 
        previous_command = current_command;
        current_command = parse_gcode(lineBufferPointer);
        print_state(current_command);

    }

    fclose(gcodeFile);
    return 0;  // make sure your main returns int
}
