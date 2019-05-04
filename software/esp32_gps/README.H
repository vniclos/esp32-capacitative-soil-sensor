#ifndef README
#define README
/* 
 *  This project is as sample of connect  esp32 to gps
 *  Vicente Niclos, you can find me on faceboonk
------------------------------------------------------------
 HADWARE AND CONNECTIONS
------------------------------------------------------------
ESP32 devkit v1 version 36 GPIOs
GPS Module NEO-GPS 6M module
wires etc.

Connections pins
ESP32 |   GPS
--------------
3.3V    | VIN
GND     | GNDC
16(TX2) | TX
17(RX2) | RX


--------------------------------------------------------
LIBRARIES
--------------------------------------------------------
You need TinyGPS++.h and SoftwareSerial.h
you cand download on github this urls
https://github.com/mikalhart/TinyGPSPlus
https://github.com/PaulStoffregen/SoftwareSerial

* --------------------------------------------------
NOTES ABOUT DATE TIME DIFERENCES
-----------------------------------------------------
Oh! now it is the cause of why humans never arrive 
on time, we do not coordinate our watches.
LOCAL TIME:
    is the date/time of your clock or  reported by 
    your PC. If your PC clock is accurate to a 
    second then the other time scales displayed
    above will also be accurate to within one second.
UTC TIME:
    Coordinated Universal Time, popularly known as GMT
    (Greenwich Mean Time), or Zulu time. 
    Local time differs from UTC by the number of hours 
    of your timezone.
GPS TIME:
    Global Positioning System time, is the atomic time
    scale implemented by the atomic clocks in the 
    GPS ground control stations and the GPS satellites
    themselves. 
    GPS time was zero at 0h 6-Jan-1980 and since it 
    is not perturbed by leap seconds GPS is now 
    ahead of UTC by 18 seconds.
LORAM-C TIME
    Long Range Navigation time, is an atomic time scale
    implemented by the atomic clocks in Loran-C chain 
    transmitter sites. Loran time was zero at 0h 1-Jan-1958
    and since it is not perturbed by leap seconds it is 
    now ahead of UTC by 27 seconds.
TAI TIME:
    temps Atomique International, is the international
    atomic time scale based on a continuous counting of the
    SI second. TAI is currently ahead of UTC by 37 seconds.
    TAI is always ahead of GPS by 19 seconds. 

You can see the diferences in this instant on
http://www.leapsecond.com/java/gpsclock.htm


------------------------------------------------------------
Legal Disclaimer and Notices
------------------------------------------------------------
the software  is distributed 'as is' and with no warranties 
of any kind, whether express or implied, including and without
limitation, any warranty of merchantability 
or fitness for a particular purpose.
The user (you) must assume the entire risk of using the software.

*/

#endif
