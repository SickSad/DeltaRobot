#include "hardware.h"

void wait(int delay){
	int i = 0;
	for (i = 0; i < delay; i++)	/* Wait a bit. */
		__asm__("nop");
}

void calibrate(int up_count, int down_count){
	int count =0;
	for (count =0; count<up_count; count++){
    	step_motors(1, 1, 1, 1, 1, 1, 0, 0, 400);
    	wait(10000);
    }
    for (count =0; count<down_count; count++){
    	step_motors(0, 1, 0, 1, 0, 1, 0 ,0, 400);
    	wait(10000);
    }
}

void test_extuder(int in_count, int out_count){
	extrude(-in_count);
	extrude(out_count);
}

void extrude(int steps){
	bool dir=true;
	if (steps < 0)dir= false;
	int itter = 0;
	steps = abs(steps);

	//set the direction
	dir ? gpio_clear(GPIOA, DIR_3) : gpio_set(GPIOA, DIR_3);

	for (itter=0; itter < steps; itter++){
		wait(2000);
		gpio_clear(GPIOA, STEP_3);
		wait(2000);
		gpio_set(GPIOA, STEP_3);
	}
}

void set_spindle(bool state){
	if(state){
		gpio_set(GPIOC, SPINDLE);
	}else{
		gpio_clear(GPIOC, SPINDLE);		
	}
}


void step_motors(bool z0_dir, bool z0_step, bool z1_dir, bool z1_step, bool z2_dir, bool z2_step, bool e_dir, bool e_step, int delay){
	wait(delay);

	//toggle LED's (I think, check this on the board)
	z0_step ? gpio_toggle(GPIOD, GPIO12): NULL;
	z1_step ? gpio_toggle(GPIOD, GPIO13): NULL;
	z2_step ? gpio_toggle(GPIOD, GPIO14): NULL;

	//set the direction
    z0_dir ? gpio_clear(GPIOA, DIR_0) : gpio_set(GPIOA, DIR_0);
    z1_dir ? gpio_clear(GPIOA, DIR_1) : gpio_set(GPIOA, DIR_1);
    z2_dir ? gpio_clear(GPIOA, DIR_2) : gpio_set(GPIOA, DIR_2);
    e_dir ? gpio_clear(GPIOA, DIR_3) : gpio_set(GPIOA, DIR_3);

    //reset the step pins
    gpio_clear(GPIOA, STEP_0);
    gpio_clear(GPIOA, STEP_1);
    gpio_clear(GPIOA, STEP_2);
    gpio_clear(GPIOA, STEP_3);

    //wait a bit
   wait(delay);
    //check limit switches havn't been hit
    u16 port_b_state = GPIOB_IDR;

    bool enable_up_0 = ((port_b_state & (1 << 0))) > 0 ? true : false;//!digitalRead(UP_LIMIT_0);
    bool enable_up_1 = ((port_b_state & (1 << 1))) > 0 ? true : false;//!digitalRead(UP_LIMIT_1);
    bool enable_up_2 = ((port_b_state & (1 << 3))) > 0 ? true : false;//!digitalRead(UP_LIMIT_2);
    bool enable_e = true;

    //check up movement
    if(z0_dir && enable_up_0 && z0_step)gpio_set(GPIOA, STEP_0);
    if(z1_dir && enable_up_1 && z1_step)gpio_set(GPIOA, STEP_1);
    if(z2_dir && enable_up_2 && z2_step)gpio_set(GPIOA, STEP_2);
    if(e_dir && enable_e && e_step)gpio_set(GPIOA, STEP_3);

    //check down movement
    if(!z0_dir && z0_step)gpio_set(GPIOA, STEP_0);
    if(!z1_dir && z1_step)gpio_set(GPIOA, STEP_1);
    if(!z2_dir && z2_step)gpio_set(GPIOA, STEP_2);
    if(!e_dir && e_step)gpio_set(GPIOA, STEP_3);

	return;
}


void init_adc(){
	gpio_mode_setup(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, TEMP_ADC);
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_ADC1EN);
	adc_set_clk_prescale(ADC_CCR_ADCPRE_BY2);
	adc_disable_scan_mode(ADC1);
	adc_set_single_conversion_mode(ADC1);
	adc_set_sample_time(ADC1, ADC_CHANNEL15, ADC_SMPR1_SMP_1DOT5CYC);
	uint8_t channels[] = {ADC_CHANNEL15};
	adc_set_regular_sequence(ADC1, 1, channels);
	adc_set_multi_mode(ADC_CCR_MULTI_INDEPENDENT);
	adc_power_on(ADC1);
}

int read_adc(){
	adc_start_conversion_regular(ADC1);
	while (! adc_eoc(ADC1));
	int reg16;
	reg16 = adc_read_regular(ADC1);
	return reg16;
}

void setup_hardware(){
	rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_120MHZ]);
	rcc_peripheral_enable_clock(&RCC_AHB1ENR, RCC_AHB1ENR_IOPAEN);
	rcc_peripheral_enable_clock(&RCC_AHB1ENR, RCC_AHB1ENR_IOPBEN);
	rcc_peripheral_enable_clock(&RCC_AHB1ENR, RCC_AHB1ENR_IOPCEN); //enable port c
	rcc_peripheral_enable_clock(&RCC_AHB1ENR, RCC_AHB1ENR_IOPDEN);
	rcc_peripheral_enable_clock(&RCC_AHB2ENR, RCC_AHB2ENR_OTGFSEN);
	
	//setup the GPIO pins
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO11 | GPIO12);
	gpio_set_af(GPIOA, GPIO_AF10, GPIO9 | GPIO11 | GPIO12);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
	//Setup motor control
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, STEP_0 | DIR_0 | STEP_1 | DIR_1 | STEP_2 | DIR_2 | STEP_3 | DIR_3 );
	gpio_clear(GPIOA, STEP_0 | DIR_0 | STEP_1 | DIR_1 | STEP_2 | DIR_2 | STEP_3 | DIR_3);
	//Setup micro-stepping
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MICROSTEP_0 | MICROSTEP_1 | MICROSTEP_2 | SPINDLE);
	gpio_set(GPIOC, MICROSTEP_0 | MICROSTEP_1 | MICROSTEP_2 | SPINDLE);
	//Setup limit switches
	gpio_mode_setup(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, UP_LIMIT_0 | UP_LIMIT_1 | UP_LIMIT_2);

	init_adc();
	init_usb();
}
	
void write_serial(const char *text){
	write_serial_string(text);
}

char* read_serial(){
	usbd_poll(usbd_dev);
	return usb_buf;
}
