#include "CapacitiveMoisture.h"
#include <driver/adc.h>
#include <esp_adc_cal.h>

CapacitiveMoisture::CapacitiveMoisture() {}
CapacitiveMoisture::~CapacitiveMoisture() {}
unsigned int CapacitiveMoisture::valuePct() {
  return m_valuePct;
}
unsigned int CapacitiveMoisture::valueRead() {
  return m_valueVRead;
}
unsigned int CapacitiveMoisture::valueMin() {
  return m_valueVMin;
}
unsigned int CapacitiveMoisture::ValueMax() {
  return m_valueVMax;
}

void  CapacitiveMoisture::loop() {
  // if Lapse interval is greathan 0 wait until lapse
  // other whise read allwais
  // call in loop

  if (m_loopLapseInterval == 0)
  {
    read();
    return;
  }
  unsigned long nowMillis = millis()  ;
  if (nowMillis < m_loopLapseIntervalPrevious) {
    m_loopLapseIntervalPrevious = 0; // overflow counter
  }
  if (nowMillis - m_loopLapseIntervalPrevious > m_loopLapseInterval)
  {
    m_loopLapseIntervalPrevious = nowMillis;
    read();

  }
}

unsigned int CapacitiveMoisture::read() {

  m_count++;
  m_valueVRead = analogRead(m_pin);
  if (m_valueVRead < m_valueVMin) {
    m_valueVMin = m_valueVRead;
  }
  else if (m_valueVRead > m_valueVMax) {
    m_valueVMax = m_valueVRead;
  }
  m_valuePct = 100 - map(m_valueVRead, m_calibrateMin, m_calibrateMax, 0, 100);
  if (m_valuePct < 0) {
    m_valuePct = 0;
  }
  if (m_valuePct > 100) {
    m_valuePct = 100;
  }
  return m_valuePct;
}

void     CapacitiveMoisture::setup(unsigned short Pin, unsigned long loopReadInterval, unsigned int CalibrateMin =CALIBRATEMIN, unsigned int CalibrateMax=CALIBRATEMAX)   {
  m_pin = Pin;
  pinMode(m_pin, INPUT);
  m_loopLapseInterval = loopReadInterval;
  m_calibrateMin = CalibrateMin;
  m_calibrateMax = CalibrateMax;


}

void     CapacitiveMoisture::setLoopReadInterval(unsigned long loopLapseInterval) {
  m_loopLapseInterval = loopLapseInterval;
}
void     CapacitiveMoisture::resetCounters() {
  m_count = 0;
  m_valueVMax = 9999999 ;
  m_valueVMax = 0 ;

}
/*
  void     CapacitiveMoisture::fncReadADC1_CHANNEL_0() {
  //Reading voltage on ADC1 channel 0 (GPIO 36):
  adc1_config_width(ADC_WIDTH_BIT_10);   //Range 0-1023
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11); //ADC_ATTEN_DB_11 = 0-3,6V
  int value = adc1_get_raw( ADC1_CHANNEL_0 );
  #ifdef DEBUG_CAPACITATIVE
  {
    Serial.println(value);

  }
  #endif
  return value ;//Read analog
  }
*/
#ifdef CAPACITIVE_MOISURE_DEBUG
void CapacitiveMoisture::debugCalibration(unsigned int iRepeats, unsigned int LapseDelayMillis) {
    
  Serial.println("................");
  Serial.println("CALLIBRATION STEEPS.");
  Serial.println("1 Totally dry sensor,");
  Serial.println("2 touch the sensor with a slightly damp cloth ");
  Serial.println("3 Put the sensor in water.");
  Serial.println("4 at the end of the test observe the minimum and maximum values, ");
  Serial.println("5 Modify the program variables");
  Serial.println("  g_CallibrationMax; ");
  Serial.println("  g_CallibrationMin; ");
  Serial.println("NOTE:");
  Serial.println("Is more reliable if you lower the variable g_CallibrationMin a bit and increase the g_CallibrationMax a little");
  Serial.println("................");
  delay(10000);
  resetCounters();
  for (unsigned int i = 0; i < iRepeats; i++)
  {
    read();
    debugSerial();
    delay(LapseDelayMillis);
  }
}
void CapacitiveMoisture::debugSerial() {

  Serial.print("Count= ");
  Serial.print(m_count);

  Serial.print(" Min= ");
  Serial.print(m_valueVMin);

  Serial.print(" Read= ");
  Serial.print(m_valueVRead);


  Serial.print(" Max= ");
  Serial.print(m_valueVMax);

  Serial.print(" valuePct= ");
  Serial.print( m_valuePct);
  Serial.println("%");
}
#endif
