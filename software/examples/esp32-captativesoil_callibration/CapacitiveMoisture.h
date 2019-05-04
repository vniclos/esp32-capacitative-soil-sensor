//--------------------------------------------------
// ESP32 and Captative Soil Moisture

//..........................................
// Aut. V. Niclos
// this class is a part of dataloger project
// of testudines.org for study tortoise in wild
//-------------------------------------------

#ifndef CAPACITIVE_MOISURE_H
#define CAPACITIVE_MOISURE_H
#define CAPACITIVE_MOISURE_DEBUG
#include <arduino.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>

#define CAPACITIVE_MOISURE_DEBUG // add code for callibration and ouput Serial
#define CALIBRATEMIN 1400 // DEFAULT CALIBRATION can change on setup
#define CALIBRATEMAX 3040 // DEFAULT CALIBRATION can change on setup

class CapacitiveMoisture {

  public:
    CapacitiveMoisture();
    ~CapacitiveMoisture(void);
    unsigned int valuePct();   //return humidity as pct
    unsigned int valueRead();  //return voltage read
    unsigned int valueMin();   //return voltage min read
    unsigned int ValueMax();   //return voltage  max read
    unsigned int read() ;
    void         setup(unsigned short Pin, unsigned long loopLapseInterval, unsigned int CalibrateMin , unsigned int CalibrateMax);
    void         setLoopReadInterval(unsigned long loopReadInterval);
    void         loop();
    void         resetCounters();
    //void     fncReadADC1_CHANNEL_();
#ifdef CAPACITIVE_MOISURE_DEBUG
    void debugCalibration(unsigned int iRepeats, unsigned int LapseDelayMillis);
    void debugSerial();
#endif
  private:
    unsigned short  m_pin = 0;                     // pin were sensor is connected
    // in ESP32 is recomended use adc1 pins
    // adc2 pins is used for wifi
    int             m_calibrateMin = CALIBRATEMIN ;         //  change for our min value readed
    int             m_calibrateMax = CALIBRATEMAX ;         // change for max value readed
    unsigned long   m_loopLapseInterval = 0;        // if you call loop the sensor will read on this millis intervals only, 0=allways;
    unsigned long   m_loopLapseIntervalPrevious = 0; // is work variable for calculate loop fire read sensor
    unsigned int    m_valueVRead = 0;              // is last read
    unsigned int    m_valueVMin = 9999999 ;        // is min read since start or reset counter
    unsigned int    m_valueVMax = 0 ;              // is max read  since start or reset counter
    unsigned int    m_valuePct = 0;                // % read humidity in funcion of read value,  range m_calibrateMin and m_calibrateMax
    unsigned int    m_count = 0;                   // in number of read sensor from start or reset conuter.
};
#endif
