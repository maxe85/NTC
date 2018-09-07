# NTC
Arduino library to return tempratur in float(°C) by maxe85
for nominal temp 25°C

create an object:
NTC myNTC(analogPin,Bvalue,nominal resistance, pre resistor

get value:
myNTC.get();

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
 
