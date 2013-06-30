#include "gcode.h"
#include "hardware.h"
#include "debug.h"
#include <stdlib.h>

void setup(){
    setup_hardware();
}

int main(void)
{
	setup();
	
	char response_buffer[128];

	bool resend = false;

	GCODE_STATE previous_command; //stores the previous gcode command
    GCODE_STATE current_command; //stores the next gcode command
    init_gcode_state(&previous_command);
    init_gcode_state(&current_command);

	KINEMATIC_STATE current;
	KINEMATIC_STATE goal;
	init_kinematic_state(&current);
	init_kinematic_state(&goal);

	test_extuder(4000,4000);	
	calibrate(6000,3000);
	
	while (1){
		//should echo back any string sent to board over serial
		usbd_poll(usbd_dev);
		if(strlen(usb_buf) > 0){

			//if it's a re-sent command we don't want to overwrite the previous
			//command with something broken
			if (resend == false){
				previous_command = current_command;
			}else{
				//clear the resend
				resend = false;
			}

			current_command = parse_gcode(usb_buf);
			clear_USB_buffer();			
			current_command.x_offset = previous_command.x_offset;
			current_command.y_offset = previous_command.y_offset;
			current_command.z_offset = previous_command.z_offset;
			current_command.extrude_offset = previous_command.extrude_offset;
			//current_command.feed_rate = previous_command.feed_rate;

			//Handle checksums
			if(current_command.checksum_set){
				if (current_command.checksum != current_command.calculated_checksum){
					//if things get buggered, send a resend command
					sprintf(response_buffer, "rs %i\n", current_command.line_number);
					write_serial(response_buffer);
                    resend = true;
                    continue;
                }
			}

			//Handle GCommands
			if (current_command.g_command_set){
				//G0 Rapid move
				//G1 Controlled move
				if (current_command.g_command == 0.0f || current_command.g_command == 1.0f){
					if (current_command.x_set) goal.x = current_command.x + current_command.x_offset;
					if (current_command.y_set) goal.y = current_command.y + current_command.y_offset;
					//remember - z is inverted
					if (current_command.z_set) goal.z = (-current_command.z) + current_command.z_offset;
					if (current_command.extrude_length_set) goal.extrude_length = current_command.extrude_length + current_command.extrude_offset;

					if(current_command.feed_rate_set){
						goal.feed_rate = current_command.feed_rate;
					}else{
						//current_command.feed_rate = previous_command.feed_rate;
						//goal.feed_rate = current_command.feed_rate;
					}
					current = line_generator(current, goal, step_motors);
				}
				//G92 Set Position (without move)
				if (current_command.g_command == 92.0f){
					if (current_command.x_set){
						current_command.x_offset = current.x - current_command.x;
					}
					if (current_command.y_set){
						current_command.y_offset = current.y - current_command.y;
					}
					if (current_command.z_set){
						//remember - z is inverted
						current_command.z_offset = current.z - (-current_command.z);
					}
					if (current_command.extrude_length_set){
						current_command.extrude_offset = current.extrude_length - current_command.extrude_length;
					}
				}
			}
			
			if (current_command.m_command_set){
				//TODO: Sort the spindle code out so that it can be rotated in both directions
				//for now it is only used to control an acuator which is off or on.
				//M3 Spindle ON clockwise
				if (current_command.m_command == 3.0f){
					set_spindle(true);
				}
				//M4 Spindle ON counter-clockwise
				if (current_command.m_command == 3.0f){
					set_spindle(true);
				}
				//M5 Spindle OFF
				if (current_command.m_command == 5.0f){
					set_spindle(false);
					
				}
				//M105 get extruder temperature
				if (current_command.m_command == 105.0f){
					sprintf(response_buffer, "ok\n T:%d", read_adc());
					write_serial_string(response_buffer);
					continue;
				}
			}

			//DO NOT PUT CODE BELOW THIS POINT UNLESS THE "continue"'s in the above code
			//are taken care of or not important.

			//use the repsponse buffer because fuckit
			sprintf(response_buffer, "ok\n");
			write_serial_string(response_buffer);
		}
	}
}
