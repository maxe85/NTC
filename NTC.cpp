#include "NTC.h"


NTC::NTC( uint8_t pin, uint16_t B, uint8_t nR, uint8_t preR) :
	__pin(pin),
	__B(B),
	__nominalR(nR),
	__preR(preR)
{}

float NTC::get()
{
	uint16_t __analogRead = analogRead(__pin);
	float __ntcR = __preR * float(__analogRead) / (1023.0 - float(__analogRead));
	return ( NOMINAL_TEMP / (1- (NOMINAL_TEMP/__B) * log(__nominalR/__ntcR)) - ZERO_CELSIUS );
}



#ifdef BUFFER_SIZE

NTC *_ntc_ptr[] = {0,0};

void NTC::beginBuffer(uint32_t bufferInterval)
{
	static uint8_t index_of_pointer = 0;
	if (index_of_pointer>1)
	{
//		Serial.println(F("error: only two ntc in buffer mode possible"));
		return;
	}

	__index_of_pointer = index_of_pointer;
	_ntc_ptr[index_of_pointer++] = this; // set the global pointer
	
	TCCR1A  = 0x00; // normal timer mode
//	TCCR1B  = 0x03; // set the prescaler /64 is arduino default
	TIMSK1 |= (__index_of_pointer == 0) ? 0x02 : 0x04; // CMI enable
#ifdef AVERAGE_BUFFER_SIZE
	__bufferInterval = bufferInterval*250/AVERAGE_BUFFER_SIZE;
#else
	__bufferInterval = bufferInterval*250; // clock cycle is 250 ms at prescaler 64
#endif
	__buffer[0] = get(); // preset buffer with current value
	for (int i=1; i< BUFFER_SIZE; i++) {__buffer[i]=__buffer[0];}
	sei();	
}

float NTC::getBuffer(uint8_t last)
{
	if (last < BUFFER_SIZE )
	{
		return __buffer[ (__bufferIndex+BUFFER_SIZE-last)%BUFFER_SIZE ];
	}
	else
	{
		return __buffer[ __bufferIndex%BUFFER_SIZE];
	}
}
void NTC::handleInterrupt()
{
	if (__bufferOverflowCounter--)
	{	// don't get values if bOC and decrement it
		return;
	}
#ifdef AVERAGE_BUFFER_SIZE
	if (__average_buffer_index < AVERAGE_BUFFER_SIZE)
	{
		__average_buffer[ __average_buffer_index++ ] = get();
	}
	else
	{
	//Serial.print(__average_buffer[0]); Serial.print("\t");	
		for (uint8_t i=1; i<__average_buffer_index; i++)
		{
			
		//Serial.print(__average_buffer[i]); Serial.print("\t");
			__average_buffer[0]+= __average_buffer[i];
		}
		__buffer[ (__bufferIndex++)%BUFFER_SIZE ]  = __average_buffer[0] / __average_buffer_index;
		__average_buffer_index = 0;
	}
#else
		__buffer[ (__bufferIndex++)%BUFFER_SIZE ] = get();
#endif
	if (__index_of_pointer == 0)
	{ 
		OCR1A += (uint16_t)__bufferInterval; // set OCR to next event
	}
	else
	{
		OCR1B += (uint16_t)__bufferInterval; // set OCR to next event
	}
	__bufferOverflowCounter = __bufferInterval>>16; // timer1 is 16 bit
}

ISR(TIMER1_COMPA_vect)
{
    cli();
	
    if (_ntc_ptr[0] != 0) // if pointer to NTC object is set
    {
        _ntc_ptr[0]->handleInterrupt(); // run NTC methode
    }
    sei();
}

ISR(TIMER1_COMPB_vect)
{
    cli();
	
    if (_ntc_ptr[1] != 0) // if pointer to second NTC object is set
    {
        _ntc_ptr[1]->handleInterrupt(); // run Segm methode
    }
    sei();
}
#endif