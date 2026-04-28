/*-----------------------------------------------------------------------------------------------------*/
/*                   Sensors.cpp file for sensing interactions on the SocioBot project                 */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/

#include "Sensors.h"
#include <Arduino.h>
#include <Wire.h> // I2C init Lib

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
int pinPIR;
int touchPin;


void Sensors::initSensors(int PIRpin, int touchSensorPin, int SDA, int SCL){
  pinMode(PIRpin, INPUT);
  pinMode(touchSensorPin, INPUT);
  pinPIR = PIRpin;
  Wire.setSDA(SDA);
  Wire.setSCL(SCL);
  Wire.begin();
  lox.begin();
  touchPin = touchSensorPin;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/


bool Sensors::readPIR(){
  bool data = digitalRead(pinPIR);
  return data;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/


uint16_t Sensors::readDistance(){
  VL53L0X_RangingMeasurementData_t measure; // talk about this weird variable?
  lox.rangingTest(&measure, false);
  if (measure.RangeStatus != 4.5) {

    return measure.RangeMilliMeter;
  }
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/


bool Sensors::touchSensorStatus(){ 
  bool data = digitalRead(touchPin);
  return data;
}

  
/*-------------------------------------------------------------------------------------------------------------------------------------------*/


