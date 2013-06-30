#ifndef HARDWARE_H_INCLUDED
#define HARDWARE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <libopencm3/stm32/f4/rcc.h>
#include <libopencm3/stm32/f4/gpio.h>
#include <libopencm3/stm32/f4/adc.h>

#include "usb.h"

//I/O CONSTANTS
#define STEP_0 GPIO2 //port A pin 2
#define DIR_0 GPIO3  //port A pin 3
#define STEP_1 GPIO4 //port A pin 4
#define DIR_1 GPIO5  //port A pin 5
#define STEP_2 GPIO6 //port A pin 6
#define DIR_2 GPIO7  //port A pin 7
#define STEP_3 GPIO0 //port A pin 0
#define DIR_3 GPIO1  //port A pin 1

#define MICROSTEP_0 GPIO0 //port C pin 0
#define MICROSTEP_1 GPIO1 //port C pin 1
#define MICROSTEP_2 GPIO3 //port C pin 3

#define SPINDLE GPIO15 //port C pin 15

#define UP_LIMIT_0 GPIO0 //port B pin 0
#define UP_LIMIT_1 GPIO1 //port B pin 1
#define UP_LIMIT_2 GPIO2 //port B pin 2

#define TEMP_ADC GPIO5 //port C pin 5

void calibrate(int up_count, int down_count);
void test_extuder(int in_count, int out_count);
void extrude(int steps);
void set_spindle(bool state);
void wait(int delay);
void write_serial(const char *text);
char* read_serial();
void step_motors(bool z0_dir, bool z0_step, bool z1_dir, bool z1_step, bool z2_dir, bool z2_step, bool e_dir, bool e_step, int delay);
void init_adc();
int read_adc();
void setup_hardware();

#endif
