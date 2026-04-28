/*-----------------------------------------------------------------------------------------------------*/
/*                   Sensors.h file for sensing interactions on the SocioBot project                   */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/

#ifndef SENSORS_H
#define SENSORS_H
#include <Adafruit_VL53L0X.h> // T.O.F sensor lib

extern int pinPIR;
extern int touchPin;
class Sensors{
  public:
  void initSensors(int PIRpin, int touchSensorPin, int SDA, int SCL);
  uint16_t readDistance();
  bool readPIR();
  bool touchSensorStatus();
  int readMagnetometer(char xyz);
};
#endif
