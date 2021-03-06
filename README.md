# ESP32 CAPACITIVE SOIL MOISTURE SENSOR

![alt text](https://github.com/vniclos/esp32-capacitative-soil-sensor/blob/master/img/squematic.png?raw=true "Esp32 capacitative soil sensor" )

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

``` c++
#include "CapacitiveMoisture.h"
//-------------------------------------------

const   unsigned short g_PinSensor = 36;
const   unsigned int  g_CallibrationMin = 1400; // Default min (DRY)
const   unsigned int  g_CallibrationMax = 3040; // Default max (under water)
const   unsigned int  g_LapseInterval = 2000;   // Lapse interval read on loop
                                                // if g_LapseInterval=0 -->no lapse
CapacitiveMoisture    g_SensorCap=CapacitiveMoisture();

void setup() {
  g_SensorCap.setup(g_PinSensor, g_LapseInterval, g_CallibrationMin,  g_CallibrationMax);
  
  // if you want see callibration recomended values keep this three lines.
  // in other case remove
  unsigned int numRead=100;           // number of read for callibration
  unsigned int LapseDelayMillis=3000; //Time lapse between readings
  g_SensorCap.debugCalibration(numRead,LapseDelayMillis);
}

loop()
{
g_SensorCap.loop();
}

```
#### The output on serial port for callibration is like this image, on the las line you see the min and max values,
this is recomeneded values for g_CallibrationMin and g_CallibrationMax


![alt text](https://github.com/vniclos/esp32-capacitative-soil-sensor/blob/master/img/callibration.png?raw=true "Esp32 capacitative soil sensor" )


Contac with me on facebook 
https://www.facebook.com/vicente.niclos
