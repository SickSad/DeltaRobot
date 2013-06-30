/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2010 Gareth McMullin <gareth@blacksphere.co.nz>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "usb.h"
/*
 * This notification endpoint isn't implemented. According to CDC spec it's
 * optional, but its absence causes a NULL pointer dereference in the
 * Linux cdc_acm driver.
 */
char usb_buf[64];
usbd_device *usbd_dev;
u8 usbd_control_buffer[USB_CONTROL_BUFFER_SIZE];


static const char *usb_strings[] = {
	"Black Sphere Technologies",
	"CDC-ACM Demo",
	"DEMO",
};
/*static const char *usb_strings[] = {
	"x",
	"Matthew Shotton",
	"Delta CNC G-Code Controler",
	"PROTOTYPE",
};*/


int cdcacm_control_request(usbd_device *usbd_dev, struct usb_setup_data *req, u8 **buf,
		u16 *len, void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req))
{
	(void)complete;
	(void)buf;
	(void)usbd_dev;

	switch (req->bRequest) {
	case USB_CDC_REQ_SET_CONTROL_LINE_STATE:{ 
		/*
		 * This Linux cdc_acm driver requires this to be implemented
		 * even though it's optional in the CDC spec, and we don't
		 * advertise it in the ACM functional descriptor.
		 */
		return 1;
		}
	case USB_CDC_REQ_SET_LINE_CODING:
		if (*len < sizeof(struct usb_cdc_line_coding))
			return 0;

		return 1;
	}
	return 0;
}


void cdcacm_data_rx_cb(usbd_device *usbd_dev, u8 ep)
{
	(void)ep;

		
	int len = usbd_ep_read_packet(usbd_dev, 0x01, usb_buf, 64);
	usb_buf[len]='\0';
	//usb_buf[63] = '\n';
	/*if (len) {
		while (usbd_ep_write_packet(usbd_dev, 0x82, usb_buf, len) == 0);
		//write_serial_string(usb_buf);
	}*/

	gpio_toggle(GPIOC, GPIO5);
}

void cdcacm_set_config(usbd_device *usbd_dev, u16 wValue)
{
	(void)wValue;

	usbd_ep_setup(usbd_dev, 0x01, USB_ENDPOINT_ATTR_BULK, 64, cdcacm_data_rx_cb);
	usbd_ep_setup(usbd_dev, 0x82, USB_ENDPOINT_ATTR_BULK, 64, NULL);
	usbd_ep_setup(usbd_dev, 0x83, USB_ENDPOINT_ATTR_INTERRUPT, 16, NULL);

	usbd_register_control_callback(
				usbd_dev,
				USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
				USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
				cdcacm_control_request);
}

void clear_USB_buffer(){
	//clear the buffer
	int i = 0;
	for (i = 0; i < 64; i++){
		usb_buf[i] = '\0';
	}	
}
void write_serial_string(const char *text){
	int len = strlen(text);	
	while (usbd_ep_write_packet(usbd_dev, 0x82, text, len) == 0);
}

void write_serial_int(int i){
	char text[64];
	siprintf(text, "%i", i);
	int len = strlen(text);	
	while (usbd_ep_write_packet(usbd_dev, 0x82, text, len) == 0);
}

void init_usb(){
	usbd_dev = usbd_init(&otgfs_usb_driver, &dev, &config, usb_strings,3, usbd_control_buffer, sizeof(usbd_control_buffer));
	usbd_register_set_config_callback(usbd_dev, cdcacm_set_config);
	clear_USB_buffer();
}
