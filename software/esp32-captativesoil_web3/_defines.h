
#ifndef _DEFINES_H
#define _DEFINES_H
#include <string.h>

#define PIN_LEDINT          2   // INTERNAL LED ESP32 DEV BOARD
#define PIN_SENSOR          36

#define SNSCALLIBRATIONMIN  1400
#define SNSCALLIBRATIONMAX  3040
#define SNSLAPSEINTERVAL    2000

#define NET_WIFIMODE    "ws"          // ap=access point, other workstation
#define NET_WIFIAPSIID  "sensor"      // siid for mode workstation
#define NET_WIFIAPPWD   "123456789"  // password for mode access point
#define NET_WIFIWSSIID  "testudines"  // password for mode access point
#define NET_WIFIWSPWD   "915265ABCD"  // password  for mode workstation
#define NET_HOSTNAME    "sensors"     // name for multicasting DNS

#define CFGWIFIAPIP      "192.168.1.1"   
#define CFGWIFIAPMASK    "255.255.255.0" 

#define CFGWIFIWSIPDHCP  "0" // 0= no dhcp use STATIC IP CONFIG
#define CFGWIFIWSIP      "192.168.1.200"
#define CFGWIFIWSIPMSK   "255.255.255.0"
#define CFGWIFIWSIPGAT   "192.168.1.1"
#define CFGWIFIWSDNS1    "8.8.8.8"
#define CFGWIFIWSDNS2    "8.8.4.4"




// get short name of file name souce compilation
#define FILENAME ({ \
    const char* filename_start = __FILE__; \
    const char* filename = filename_start; \
    while(*filename != '\0') \
      filename++; \
    while((filename != filename_start) && (*(filename - 1) != '\\')) \
      filename--; \
    filename; })
#endif
