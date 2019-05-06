//javascripts

#ifndef _WEB_TODO_H
#define _WEB_TODO_H
const char g_HTML_Web_Todo[] PROGMEM = R"=====(
<fieldset><legend>Todo tasks</legend>
<h4>Configure on _defines.h</h4>
<ul>
<li>configure you wifi preferences</li>
<li>Configure sensor pin<br>Not Plug sensor on esp32 adc2 pins because is used for internal wifi</li>
<li>Calibrate your sensor</li>
<li>Compile and upload firmware</li>
</ul>
</fieldset>
<fieldset><legend>Defines config variables</legend>
<pre><code class="c++">
#define NET_WIFIMODE    "ws" 
#define NET_WIFIAPSIID  "sensor"  
#define NET_WIFIAPPWD   "123456789"    

// config in use access point mode
#define NET_WIFIWSSIID  "yourlocalwifi"    
#define NET_WIFIWSPWD   "yourlocalpasword" 
#define NET_HOSTNAME    "sensors"          

// config if accesspoint
#define CFGWIFIAPIP      "192.168.1.1"
#define CFGWIFIAPMASK    "255.255.255.0" 

//config is workstation mode
#define CFGWIFIWSIPDHCP  "0" 
#define CFGWIFIWSIP      "192.168.1.200"  
#define CFGWIFIWSIPMSK   "255.255.255.0"
#define CFGWIFIWSIPGAT   "192.168.1.1"
#define CFGWIFIWSDNS1    "8.8.8.8"
#define CFGWIFIWSDNS2    "8.8.4.4"


#define PIN_LEDINT      2            
#define PIN_SENSOR       36 

#define SNSCALLIBRATIONMIN  1400 
#define SNSCALLIBRATIONMAX  3040
#define SNSLAPSEINTERVAL    2000
</code></pre>
</fieldset>
)=====";
#endif
