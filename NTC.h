/*
 *  Arduino library to return tempratur in float(°C) by maxe85
 *  
 *  
 *  Vcc ----- pre Resistor ----- ----- NTC ----- GND
 *                                       |
 *                                       |
 *      			     uc ADCpin
 *  
*/

#ifndef NTC_h
#define NTC_h
#include "Arduino.h"


#define ZERO_CELSIUS	273.15
#define NOMINAL_TEMP	298.15

//#define BUFFER_SIZE	64 		// undefine to safe memory und don't mess with the interrupts
#ifdef BUFFER_SIZE
	#define AVERAGE_BUFFER_SIZE 8 // undefine this if you dont want to use average values
#endif

class NTC
{
	public:
		NTC( uint8_t pin, uint16_t B, uint8_t nR, uint8_t preR);		// Arduino analogPin, B-value, nominal resistor, pre resistor
		float get();
	#ifdef BUFFER_SIZE 
		void beginBuffer(uint32_t bufferInterval);	// set timer interrupt for storing data to buffer
		float getBuffer(uint8_t last);							// get the x-last buffer entry
		void handleInterrupt();
	#endif
		
	private:
		uint8_t	__pin;
		uint16_t	__B;
		uint16_t	__nominalR;
		uint16_t	__preR;
	#ifdef BUFFER_SIZE
		uint8_t	__index_of_pointer;
		uint32_t	__bufferInterval = 0;
		uint16_t	__bufferOverflowCounter;
		float	__buffer[BUFFER_SIZE];
		uint8_t	__bufferIndex = 0;
	#endif
	#ifdef AVERAGE_BUFFER_SIZE
		float	__average_buffer[AVERAGE_BUFFER_SIZE];
		uint8_t	__average_buffer_index = 0;
	#endif
};

#endif
