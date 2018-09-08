//analog Pins
#define NTC_PIN     7

#include "NTC.h"

NTC ntc0(NTC_PIN,4300,22,22); // Arduino analogPin, B-value, nominal resistor, pre resistor
void setup()
{
  Serial.begin(9600);
  
                            //begin interrupt controlled value buffer, get value every 200 ms
//  ntc0.beginBuffer(125); 
                            // you neet to define BUFFER_SIZE in NTC.h to use buffer to do so
}

void loop()
{
delay(2000);

Serial.println(ntc0.get()); // this does not give average values in buffer mode

/*
                            // define BUFFER_SIZE in NTC.h to use buffer
Serial.print(ntc0.getBuffer(1)); // get latest value in buffer
Serial.print("\t");
Serial.print(ntc0.getBuffer(2));
Serial.print("\t");
Serial.print(ntc0.getBuffer(3));
Serial.print("\t");
Serial.print(ntc0.getBuffer(4));
Serial.print("\t");
Serial.print(ntc0.getBuffer(5));
Serial.print("\t");
Serial.print(ntc0.getBuffer(6));
Serial.print("\t");
Serial.print(ntc0.getBuffer(7));
Serial.print("\t");
Serial.println(ntc0.getBuffer(0));  // get oldest value with 0 or >= BUFFER_SIZE
*/
}


