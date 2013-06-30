#ifndef GCODE_H_INCLUDED
#define GCODE_H_INCLUDED

#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#define RAW_STRING_LENGTH 128

typedef struct GCODE_STATE_TAG{
    char raw_string[RAW_STRING_LENGTH];

    int calculated_checksum;
    int line_number;
    bool line_number_set;
    int checksum;
    bool checksum_set;
    
    float x;
    bool x_set;
    float y;
    bool y_set;
    float z;
    bool z_set;
    
    float extrude_length;
    bool extrude_length_set;
    float feed_rate;
    bool feed_rate_set;
    float tool_number;
    bool tool_number_set;
    
    float g_command;
    bool g_command_set;
    float m_command;
    bool m_command_set;
    
    float s_parameter;
    bool s_parameter_set;
    float p_parameter;
    bool p_parameter_set;
    float r_parameter;
    bool r_parameter_set;

    float x_offset;
    float y_offset;
    float z_offset;
    float extrude_offset;
} GCODE_STATE;

void init_gcode_state(GCODE_STATE *s);
GCODE_STATE parse_gcode(char *str);

#endif