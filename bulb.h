/*
**  LIFX C Library
**  Copyright 2016 Linard Arquint
*/

#ifndef BULB_H
#define BULB_H

#include <stdint.h>


typedef struct {
	/** IP addr */
	unsigned long in_addr;
	/** MAC addr */
	uint64_t target;
	/** should be 1 (UDP) */
    uint8_t service;
    uint32_t port;
} bulb_service_t;

#endif
/*
**  LIFX C Library
**  Copyright 2016 Linard Arquint
*/

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>


typedef struct {
	/** 0 - 65535 */
	uint16_t hue;
	/** 0 - 65535 */
	uint16_t saturation;
	/** 0 - 65535 */
	uint16_t brightness;
	/** 2500° - 9000° */
	uint16_t kelvin;
} color_t;

#endif
