/*-----------------------------------------------------------------------------------------------------*/
/*                       Buzzer.h file for audio control on the SocioBot project                       */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/


#ifndef BUZZER_H
#define BUZZER_H
#include <Arduino.h>
extern int buzzerPin;
class Buzzers{
  public:
  void initBuzzer(int pin);
  void powerOnChime();
  void gameWinChime();
  void playBeep();
  void playLevelUp();
  void playGameOver();
  void playEQUALS();
  void playpetBeep();
};
#endif
