# ESP32 CAPACItIVE SOIL MOISTURE

![alt text](![alt text](https://github.com/vniclos/esp32-capacitative-soil-sensor/blob/master/img/squematic.png"Robot ARM4X builded" )
 "Robot ARM4X builded" )
?raw=true
## Hardware

- 1 ESP32 DEVKIT V1
- 1 Capacitive soil moisture v1.2 (connected 3.3v)
- 1 Resistance 1k
- 1 Resistance 0.390k
- 1 Power suply 5v 2a

Note:
On ESP32 is better not use ADC2 pins becouse is used
for wifi functions.

## Software
- Arduino IDE

## I have develop a simple class interface.

### You can get 
% Humidity of soil.
value read
Max read value
Min read value
Callibrate function 


### Easy use ###

Example:

#include "CapacitiveMoisture.h"
//-------------------------------------------

const   unsigned short g_PinSensor = 36;
const   unsigned int  g_CallibrationMin = 1400; // Default min (DRY)
const   unsigned int  g_CallibrationMax = 3040; // Default max (under water)
const   unsigned int  g_LapseInterval = 2000;   // Lapse interval read on loop
                                                // if g_LapseInterval=0 -->no lapse
void setup() {
  g_SensorCap.setup(g_PinSensor, g_LapseInterval, g_CallibrationMin,  g_CallibrationMax);
}




Contac with me on facebook 
https://www.facebook.com/vicente.niclos
