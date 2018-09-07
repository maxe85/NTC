/*
 *  Arduino library to return tempratur in float(°C) by maxe85
 *  
 *  
 *  Vcc ----- pre Resistor ----- ----- NTC ----- GND
 *                                       |
 *                                       |
 *      			     uc pin
 *  
*/

#ifndef NTC_h
#define NTC_h
#include "Arduino.h"


#define ZERO_CELSIUS 273.15
#define NOMINAL_TEMP 298.15
//#define DEBUG_MODE


class NTC
{
	public:
		NTC( uint8_t pin, uint16_t B, uint8_t nR, uint8_t preR); // Arduino pin, B-value, nominal resistor, pre resistor
		float get();
		
	private:
		uint8_t  __pin;
		uint16_t __B;
		uint16_t __nominalR;
		uint16_t __preR;
};

#endif
