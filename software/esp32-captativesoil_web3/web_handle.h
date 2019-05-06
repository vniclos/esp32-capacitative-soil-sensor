#ifndef _WEB_HANDLE_H
#define _WEB_HANDLE_H
// file for handle web server request events
#include "_defines.h"
#include "_extern.h"
#include "web_root.h"
#include "web_js.h"
#include "web_css.h"
#include "web_todo.h"
#include "Cls_Utils.h"
//=================================================
void handleROOT() {
  // Serial.println("handleRoot");
  digitalWrite(g_PinLedInt, 1);

  g_server.send(200, "text/html", g_HTML_Web_root);
  digitalWrite(g_PinLedInt, 0);
}
//=================================================
void handleJS() {
  // Serial.println("handleJS");
  digitalWrite(g_PinLedInt, 1);
  g_server.send(200, "application/javascript", g_HTML_Web_JS);
  digitalWrite(g_PinLedInt, 0);
}

//=================================================
void handleCSS() {
  // Serial.println("handleCSS");
  digitalWrite(g_PinLedInt, 1);
  g_server.send(200, "text/css", g_HTML_Web_CSS);
  digitalWrite(g_PinLedInt, 0);
}

//=================================================
void handleDiagramSvg()
{
  digitalWrite(g_PinLedInt, 1);
  String szHtml = "";

  szHtml += "<pre>";
  szHtml += "";
  szHtml += "Hadware";
  szHtml += "\n 1- ESP32 DEVELOPER KIT";
  szHtml += "\n 2. Captative soil moisture sensor v1.2";
  szHtml += "\n 3. Added resistence divisor 1k and 0.960k por voltage [0-1] ";
  szHtml += "\n 4  Connection pin diagram voltage divisor for data pin ";
  szHtml += "\n";
  szHtml += "\n  ESP32                             SENSOR";
  szHtml += "\n  3.3V  ---------------------------   +";
  szHtml += "\n  GND   ---------------------------   -";
  szHtml += "\n          |   0.920K         1K";
  szHtml += "\n          |- \\\\---- X---\\\\\----   DATA";
  szHtml += "\n                      |";
  szHtml += "\n  PIN36 --------------|";
  szHtml += "\n                EP32-PIN";
  szHtml += "\nNote:";
  szHtml += "\nRemember in esp32 ADC2 pins are used for wifi function";
  szHtml += "\nbetter use ADC1";
  szHtml += "</pre>";
  g_server.send(200, "text/html", szHtml);
  digitalWrite(g_PinLedInt, 0);
}
//=================================================

//=================================================
void handleReadSensors() {
  Serial.println("handleReadSensors");
  digitalWrite(g_PinLedInt, 1);
  //g_DL_LastReadRTCDate g_DL_LastReadRTCTime
  String szHtml = "";
  szHtml += "<fieldset><legend>Soil humidity </legend>\n";
  szHtml += "<br/><span class = \"fldtit\">Humidity :</span><span class=\"fldvalue\">" + String(g_snsCapMoisture.valuePct()) + "</span>";
  szHtml += "<br/><span class =\"fldtit\">Read:</span><span class=\"fldvalue\">" + String(g_snsCapMoisture.valueRead()) + "</span>";
  szHtml += "<br/><span class =\"fldtit\">Min.:</span><span class=\"fldvalue\">" + String(g_snsCapMoisture.valueMin()) + "</span>";
  szHtml += "<br/><span class =\"fldtit\">Max.:</span><span class=\"fldvalue\">" + String(g_snsCapMoisture.ValueMax()) + "</span>";

  szHtml += "<object data=\"/image.svg\" type=\"image/svg+xml\"></object>";

  szHtml += "</fieldset>";
  szHtml += "<p>Id Fimware: " + String( g_firmware) + "</p>";
  g_server.send(200, "text/html", szHtml);
  digitalWrite(g_PinLedInt, 0);

}
//=================================================
void handleNotFound() {
  Serial.println("handleNotFound");
  digitalWrite(g_PinLedInt, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += g_server.uri();
  message += "\nMethod: ";
  message += (g_server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += g_server.args();
  message += "\n";
  for (uint8_t i = 0; i < g_server.args(); i++) {
    message += " " + g_server.argName(i) + ": " + g_server.arg(i) + "\n";
  }

  g_server.send(404, "text/plain", message);
  digitalWrite(g_PinLedInt, 0);
}
//=================================================
void handleFirmware() {
  digitalWrite(g_PinLedInt, 1);
  g_server.send(200,  "image/svg+xml", g_firmware);
  digitalWrite(g_PinLedInt, 0);
}
//=================================================
void handleTodo() {
  // Serial.println("handleTodo");
  digitalWrite(g_PinLedInt, 1);

  g_server.send(200, "text/html", g_HTML_Web_Todo);
  digitalWrite(g_PinLedInt, 0);
}

//=================================================
#endif
