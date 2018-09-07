#include "NTC.h"


NTC::NTC( uint8_t pin, uint16_t B, uint8_t nR, uint8_t preR) :
	__pin(pin),
	__B(B),
	__nominalR(nR),
	__preR(preR){}

float NTC::get()
{
	uint16_t __analogRead = analogRead(__pin);
	float __ntcR = __preR * float(__analogRead) / (1023.0 - float(__analogRead));
	return ( NOMINAL_TEMP / (1- (NOMINAL_TEMP/__B) * log(__nominalR/__ntcR)) - ZERO_CELSIUS );
}
