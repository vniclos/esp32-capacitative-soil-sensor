
#include "CapacitiveMoisture.h"

//----------------------------------------------
// convention
// used g_ prefix for globlal variables
// used m_ prexix for internal class variables
// other is for internal fuction variables
///-------------------------------------------
const   unsigned short g_PinSensor = 36;
const   unsigned int  g_CallibrationMin = 1400;
const   unsigned int  g_CallibrationMax = 3040;
const   unsigned int  g_LapseInterval = 2000;
CapacitiveMoisture    g_SensorCap=CapacitiveMoisture();
//---------------------------------------------
//---------------------------------------------
void fncCallibration(){ 



  unsigned int numRead=100;           // number of read for callibration
  unsigned int LapseDelayMillis=3000; //Time lapse between readings
  g_SensorCap.debugCalibration(numRead,LapseDelayMillis);
  }
  //---------------------------------------------
  //---------------------------------------------
void setup() {
  Serial.begin(115200);
  g_SensorCap.setup(g_PinSensor, g_LapseInterval, g_CallibrationMin,  g_CallibrationMax);
  fncCallibration();  
   Serial.println("END SETUP...............................");
}
//---------------------------------------------//---------------------------------------------
void loop() {

  g_SensorCap.loop();
  // put your main code here, to run repeatedly:

}
