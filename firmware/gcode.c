#include "gcode.h"


void init_gcode_state(GCODE_STATE *s){
    (*s).raw_string[RAW_STRING_LENGTH -1] = '\0';
    (*s).calculated_checksum = 0;
    (*s).line_number = 0;
    (*s).line_number_set = false;
    (*s).checksum = 0;
    (*s).checksum_set = false;
    
    (*s).x = 0.0f;
    (*s).x_set = false;
    (*s).y = 0.0f;
    (*s).y_set = false;
    (*s).z = 0.0f;
    (*s).z_set = false;
    
    (*s).extrude_length = 0.0f;
    (*s).extrude_length_set = false;
    (*s).feed_rate = 0.0f;
    (*s).feed_rate_set = false;
    (*s).tool_number = 0;
    (*s).tool_number_set = false;
    
    (*s).g_command = 0.0f;
    (*s).g_command_set = false;
    (*s).m_command = 0.0f;
    (*s).m_command_set = false;
    
    (*s).s_parameter = 0.0f;
    (*s).s_parameter_set = false;
    (*s).p_parameter = 0.0f;
    (*s).p_parameter_set = false;
    (*s).r_parameter = 0.0f;
    (*s).r_parameter_set = false;

    (*s).x_offset= 0.0f;
    (*s).y_offset= 0.0f;
    (*s).z_offset= 0.0f;
    (*s).extrude_offset= 0.0f;
}



GCODE_STATE parse_gcode(char *str){
    //create the current state to be filled
    GCODE_STATE current_state;
    //init it to blank
    init_gcode_state(&current_state);

    current_state.line_number = 0;
    current_state.calculated_checksum = 0;
    current_state.checksum = 0;
    strcpy(current_state.raw_string, str);

    while(*str != 0){
        
        switch(*str){
            case '*':
                //checksum
                current_state.calculated_checksum &= 0xff;
                if(sscanf(str,"*%i",&current_state.checksum)){
                    current_state.checksum_set = true;
                }
                //TODO: Move this to a better place to handle it
                /*if (current_state.checksum != current_state.calculated_checksum){
                    printf("rs %i\n", current_state.line_number);
                }*/
                break;
            case 'N':
                //line number
                if(sscanf(str,"N%i",&current_state.line_number)){
                    current_state.line_number_set = true;
                }
                break;
            case 'T':
                //tool number
                if(sscanf(str,"T%f",&current_state.tool_number)){
                    current_state.tool_number_set= true;
                }
                break;
            case 'G':
                //Standard Gcode command
                if(sscanf(str,"G%f",&current_state.g_command)){
                    current_state.g_command_set= true;
                }
                break;
            case 'M':
                //Rep-rap defined command
                if(sscanf(str,"M%f",&current_state.m_command)){
                    current_state.m_command_set= true;
                }
                break;
            case 'R':
                //temperature
                if(sscanf(str,"R%f",&current_state.r_parameter)){
                    current_state.r_parameter_set= true;
                }
                break;
            case 'F':
                //feedrate
                if(sscanf(str,"F%f",&current_state.feed_rate)){
                    current_state.feed_rate_set = true;
                }
                break;
            case 'S':
                //command parameter
                if(sscanf(str,"S%f",&current_state.s_parameter)){
                    current_state.s_parameter_set= true;
                }
                break;
            case 'P':
                //command parameter
                if(sscanf(str,"P%f",&current_state.p_parameter)){
                    current_state.p_parameter_set= true;
                }
                break;
            case 'E':
                //length of extrudate
                if(sscanf(str,"E%f",&current_state.extrude_length)){
                    current_state.extrude_length_set = true;
                }
                break;
            case 'X':
                //A X co-ordinate
                if(sscanf(str,"X%f",&current_state.x)){
                    current_state.x_set = true;
                }
                break;
            case 'Y':
                //A Y co-ordinate
                if(sscanf(str,"Y%f",&current_state.y)){
                    current_state.y_set = true;
                }
                break;
            case 'Z':
                //A Z co-ordinate
                if(sscanf(str,"Z%f",&current_state.z)){
                    current_state.z_set = true;
                }
                break;
            case ';':
                //comment
                while (*str != 0)str++; //ignore rest of line
                str--; //decrement, because we increment at the end of this switch
                break;
        }
        //calculate the checksum
        if (current_state.checksum_set != true){
            current_state.calculated_checksum = current_state.calculated_checksum ^ *str;
        }
        //increment to next character in string
        str++;
    }
    return current_state;
}



