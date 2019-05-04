/*----------------------------------
   ESP32 GPS EXAMPLE. Vicente Niclos 2019
   Please, for information connection...
   read README.H
*/
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define GPS_PIN_RX 16
#define GPS_PIN_TX 17
#define GPS_BAUDS 9600

TinyGPSPlus    g_gps;
SoftwareSerial g_gpsSerial(GPS_PIN_RX, GPS_PIN_TX);
bool  g_gpsIsAccesible = false;
bool  g_gpsLastRead_IsAccesibleLocation = false;
bool  g_gpsLastRead_IsAccesibleDate = false;
bool  g_gpsLastRead_IsAccesibleTime = false;
char  g_DL_LastRead_GpsLoc[32] = "\0";      // Latitud and longitud in decimal format
char  g_DL_LastRead_GpsAlt[6] = "\0";       // Altitud in meters
char  g_DL_LastRead_GpsDateTime[32] = "\0"; // GPS system time,bit diferent of UTC
                                          
char g_URL_start[]="http://www.google.com/maps/place/";
char g_URL[60]="/0";
unsigned int g_gps_iCountRead = 0;
//--------------------------------------------
// SETUPS FUNCTIONS
//--------------------------------------------
void fncSetupGPS()
{
  // Start the software serial port for access to GPS
  // Remember during the first minutes two GPS data will not be available.
  // The reason is that the gps takes time to scan the satellites to connect to.
  g_gpsSerial.begin(GPS_BAUDS);
}

void setup() {
  Serial.begin(115200);
  fncSetupGPS();
  Serial.println("Started");
  Serial.println("Please, wait while the gps locates the satellites");
}
//--------------------------------------------
// LOOP FUNCTIONS
//--------------------------------------------
void fncLoopGPS_PrintSerial()
{
   Serial.print("GPS CountRead=");
  Serial.println(g_gps_iCountRead);
  
  Serial.print("g_gpsIsAccesible=");
  Serial.println(g_gpsIsAccesible);
  if (!g_gpsIsAccesible) {
    Serial.println("GPS NOT DETECTED, Where are the pins?");
  }

  Serial.print("g_gpsLastRead_IsAccesibleLocation=");
  Serial.println(g_gpsLastRead_IsAccesibleLocation);
  Serial.print("g_gpsLastRead_IsAccesibleDate=");
  Serial.println(g_gpsLastRead_IsAccesibleDate);
  Serial.print("g_gpsLastRead_IsAccesibleTime=");
  Serial.println(g_gpsLastRead_IsAccesibleTime);

 
  Serial.print("g_DL_LastRead_GpsLoc=");
  Serial.println(g_DL_LastRead_GpsLoc);
  Serial.print("g_DL_LastRead_GpsAlt=");
  Serial.println(g_DL_LastRead_GpsAlt);
  Serial.print("g_DL_LastRead_GpsDateTime=");
  Serial.println(g_DL_LastRead_GpsDateTime);
  Serial.print("URL for googlemap= ");
  
  strcpy (g_URL,g_URL_start);
  strcat(g_URL,g_DL_LastRead_GpsLoc);
  Serial.println(g_URL);
  Serial.println(".........\n");
}


void fncLoopGPS_FillFlds() {
  g_gps_iCountRead++;
 
  if (g_gps.location.isValid()) {
    sprintf(g_DL_LastRead_GpsLoc, "%0.6f, %0.6f",  g_gps.location.lat(), g_gps.location.lng());
    sprintf(g_DL_LastRead_GpsAlt, "%0.0f", g_gps.altitude.meters());
    g_gpsLastRead_IsAccesibleLocation = true;

  }


  if (g_gps.time.isValid() && g_gps.date.isValid())
  {
    sprintf(g_DL_LastRead_GpsDateTime, "%04u/%02u/%02u %02u:%02u:%02u:%02u", g_gps.date.year(), g_gps.date.month(), g_gps.date.day(),
            g_gps.time.hour(), g_gps.time.minute(), g_gps.time.second(), g_gps.time.second(), g_gps.time.centisecond());
    if (g_gps.time.isValid()) {
      g_gpsLastRead_IsAccesibleTime = true;
    }
    if (g_gps.date.isValid()) {
      g_gpsLastRead_IsAccesibleDate = true;
    }

  }
  fncLoopGPS_PrintSerial();



}
// Tray connect to gps satelit
// remember the on start the gps look for satelits
// and spend some minutes.
void fncLoopGPS_Read()
{
  g_gpsIsAccesible = false;
  g_gpsLastRead_IsAccesibleLocation = false;
  g_gpsLastRead_IsAccesibleDate = false;
  g_gpsLastRead_IsAccesibleTime = false;

  while (g_gpsSerial.available() > 0)
  {
    if (g_gps.encode(g_gpsSerial.read()))
    {
      g_gpsIsAccesible = true;
      fncLoopGPS_FillFlds();
      delay(5000);
    }


    if (millis() > 5000 && g_gps.charsProcessed() < 10)
    {
      g_gpsIsAccesible = false;
      while (true);
    }
  }
}
void loop() {

  fncLoopGPS_Read();



}
