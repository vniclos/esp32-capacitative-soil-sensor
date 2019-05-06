/*
  Utility for  homogenous share  between global variables betwen <file>.h
*/

#ifndef _EXTERN
#define _EXTERN

#include "Cls_Utils.h"
#include "_defines.h"
#include "CapacitiveMoisture.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

extern WebServer            g_server;
// change values in defines.h
extern const char* g_Net_WifiMode   ;          // ap=access point, other workstation
extern const char* g_Net_WifiAPSsid; // siid for mode accces point
extern const char* g_Net_WifiAPPwd  ; // password for mode access point
extern const char* g_Net_WifiWSSsid ; // siid for mode workstation
extern const char* g_Net_WifiWSPwd  ; // password  for mode workstation
extern const char* g_Net_HostName  ; // name for multicasting DNS
//wifi values in use after the start
extern char          g_cfgWifiWsIPDHCP[3];
extern  char         g_wifi_Ssid[33];
extern  char         g_wifi_Pwd[33];
extern  char         g_wifi_IP[16];

extern const unsigned short g_PinLedInt;
extern const unsigned short g_PinSensor;
extern const unsigned int   g_SnsCallibrationMin ;
extern const unsigned int   g_SnsCallibrationMax ;
extern const unsigned int   g_snsLapseInterval ;
extern CapacitiveMoisture   g_snsCapMoisture;


extern char  g_firmware[128] ;
#endif
