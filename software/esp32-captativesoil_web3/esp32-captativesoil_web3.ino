//-------------------------------------------------
// convection g_ is globlal objects and variables
// change next g_NET to your eviroment preferences
//-------------------------------------------------
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include  "Cls_Utils.h"
#include "web_handle.h"     // Web events funcions
#include "web_root.h"       // web content /              
#include "web_js.h"         // web content /js.js  
#include "web_css.h"        // web content /css.css
#include "web_todo.h"       // web content /todo  (ajax filled)
#include "CapacitiveMoisture.h"
//-------------------------------------------------
//-------------------------------------------------
// change values in defines.h
Cls_Utils *g_Utils = Cls_Utils::Instance();
const char* g_Net_WifiMode   = NET_WIFIMODE;   // ap=access point, other workstation
const char* g_Net_WifiAPSsid = NET_WIFIAPSIID; // siid for mode accces point
const char* g_Net_WifiAPPwd  = NET_WIFIAPPWD;  // password for mode access point
const char* g_Net_WifiWSSsid = NET_WIFIWSSIID; // siid for mode workstation
const char* g_Net_WifiWSPwd  = NET_WIFIWSPWD;  // password  for mode workstation
const char* g_Net_HostName   = NET_HOSTNAME;   // name for multicasting DNS
// in use after the start
char          g_cfgWifiWsIPDHCP[3] = NET_WIFIMODE;
char         g_wifi_Ssid[33] = "/0";
char         g_wifi_Pwd[33]  = "/0";
char         g_wifi_IP[16]   = "/0";

const   unsigned short g_PinLedInt = PIN_LEDINT;
const   unsigned short g_PinSensor = PIN_SENSOR;

const   unsigned int   g_SnsCallibrationMin = SNSCALLIBRATIONMIN;
const   unsigned int   g_SnsCallibrationMax = SNSCALLIBRATIONMAX;
const   unsigned int   g_snsLapseInterval   = SNSLAPSEINTERVAL;
CapacitiveMoisture     g_snsCapMoisture     = CapacitiveMoisture();

char  g_firmware[128] = "/0"; // name of firmware in use
char  g_urlRoot[128] = "/0"; //  mdns uri
WebServer   g_server(80);
//-------------------------------------------------
//-------------------------------------------------
void fncCallibration()
{ delay(100);
  Serial.println("Reading");
  Serial.println("CALLIBRATION STEEPS.");
  Serial.println("1 Totally dry sensor,");
  Serial.println("2 touch the sensor with a slightly damp cloth ");
  Serial.println("3 Put the sensor in water.");
  Serial.println("4 at the end of the test observe the minimum and maximum values, ");
  Serial.println("5 Modify the program variables");
  Serial.println("  g_SnsCallibrationMax; ");
  Serial.println("  g_SnsCallibrationMin; ");
  Serial.println("6  is more reliable if you lower the variable g_SnsCallibrationMin a bit and increase the g_SnsCallibrationMax a little");
  delay(10000);


  unsigned int numRead = 100;         // number of read for callibration
  unsigned int lapseMillis = 3000; //Time lapse between readings
  g_snsCapMoisture.debugCalibration(numRead, lapseMillis);
}
//-------------------------------------------------
//-------------------------------------------------

void setup_hardware() {
  Serial.begin(115200);
  g_snsCapMoisture.setup(g_PinSensor, g_snsLapseInterval, g_SnsCallibrationMin,  g_SnsCallibrationMax);
  Serial.println("----------------------------------");
  strcpy(g_firmware, FILENAME);
  strcat(g_firmware, " ");
  strcat(g_firmware, __DATE__);
  strcat(g_firmware, " ");
  strcat(g_firmware, __TIME__);
  Serial.println(g_firmware);
  Serial.println("----------------------------------");
}
bool setup_NetWorkWS() {
  bool bReturn=true;
  strcpy(g_wifi_Ssid, g_Net_WifiWSSsid);
  strcpy(g_wifi_Pwd, g_Net_WifiWSPwd);

  WiFi.mode(WIFI_STA);
  // if CFGWIFIWSIPDHCP  "0" then static ip (on defines.h)
  if (CFGWIFIWSIPDHCP == "0") {
    IPAddress ip      = g_Utils->fncWifi_String2IP4(CFGWIFIWSIP);
    IPAddress ipMask  = g_Utils->fncWifi_String2IP4(CFGWIFIWSIPMSK);
    IPAddress ipGateway = g_Utils->fncWifi_String2IP4(CFGWIFIWSIPGAT);
    IPAddress ipDNS1 = g_Utils->fncWifi_String2IP4(CFGWIFIWSDNS1);
    IPAddress ipDNS2 = g_Utils->fncWifi_String2IP4(CFGWIFIWSDNS2);
    if (!WiFi.config(ip, ipGateway, ipMask, ipDNS1, ipDNS2)) {
      Serial.println("STA Failed to configure");
    }
    else {
      Serial.println("MOde WS with static ip");
    }
  }
  WiFi.begin(g_wifi_Ssid , g_wifi_Pwd);
  // Wait for connection if cant connet go to default factory mode
  unsigned int iCount = 15;
  while (WiFi.status() != WL_CONNECTED && iCount > 0) {
    iCount--;
    delay(500);
    Serial.print(".");
     
  }
  if (iCount == 0)  {
    Serial.println("Fail to connect with wifi mode workstaion ");
    Serial.println("try Start wifi mode access point");
    bReturn=false;
  }

  Serial.println("Wifi mode workstaion ");
  Serial.print("Connected to ");
  Serial.println(g_wifi_Ssid);
  IPAddress myIP = WiFi.localIP();
  Serial.print("IP address: ");
  Serial.println(myIP);
  strcpy( g_wifi_IP, (g_Utils->fncWifi_IP42String(myIP)).c_str());
  return true;

}
void setup_NetWorkAP() {
  WiFi.mode(WIFI_AP);
  strcpy (g_wifi_Ssid, g_Net_WifiAPSsid);
  strcpy (g_wifi_Pwd, g_Net_WifiAPPwd);
  WiFi.softAP(g_wifi_Ssid, g_wifi_Pwd);
  delay(2000);
  IPAddress ip = g_Utils->fncWifi_String2IP4(CFGWIFIAPIP); //192.168.1.1
  IPAddress ipMask = g_Utils->fncWifi_String2IP4(CFGWIFIAPMASK);
  IPAddress ipGateway = ip; // set gateway to match your network
  WiFi.softAPConfig(ip, ipGateway, ipMask);
  delay(100);
  strcpy (g_wifi_IP, g_Utils->fncWifi_IP42String(WiFi.softAPIP()).c_str() );
  Serial.print("AP IP address: ");
  Serial.println(g_wifi_IP);
  delay(1000);
}
void setup_NetworkMdns() {
  sprintf(g_urlRoot, "http://%s.local", g_Net_HostName);

  if (!MDNS.begin(g_Net_HostName)) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  else
  {
    Serial.print("mDNS responder at " + String(g_urlRoot));
  }

  MDNS.addService("http", "tcp", 80);
  Serial.println("mDNS responder started at :" + String(g_urlRoot));

}
void setup_Network() {

  if (strcmp(g_Net_WifiMode, "ap") == 0) {
    setup_NetWorkAP();
  }
  else if (!setup_NetWorkWS()) {
    setup_NetWorkAP();
  }

  if (!MDNS.begin(g_Net_HostName)) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  setup_NetworkMdns();

}
void setup_Web() {
  g_server.on("/", handleROOT);
  g_server.on("/js.js", handleJS);
  g_server.on("/css.css", handleCSS);
  g_server.on("/refresh", handleReadSensors);
  g_server.on("/readsensors", handleReadSensors);
  g_server.on("/fncTodo", handleTodo);
  g_server.on("/diagram.svg", handleDiagramSvg);
  g_server.begin();
  Serial.println("web server started");

}
void setup(void) {
  setup_hardware();
  setup_Network();
  setup_Web();
}
void loop(void) {
  g_snsCapMoisture.loop();
  g_server.handleClient();
}
