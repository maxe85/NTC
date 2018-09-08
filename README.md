# NTC
Arduino library to return tempratur in float(°C) by maxe85

circuit:
 Vcc
  |
 pre Resistor
  |
  -----> adc pin
  |
 NTC
  |
 GND

create an object:
NTC myNTC(analogPin,Bvalue,nominal resistance, pre resistor)

get value:
myNTC.get(); // returns float

added support for buffering values
define BUFFER_VALUE in NTC.h
init it in setup()
{
 myNTC.beginBuffer(bufferInterval in ms);
}
getValue
