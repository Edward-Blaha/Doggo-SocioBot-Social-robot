/*-----------------------------------------------------------------------------------------------------*/
/*                       Buzzers.cpp file for audio control on the SocioBot project                    */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/

#include "Buzzers.h"
int buzzerPin;
void Buzzers::powerOnChime(){
  tone(buzzerPin, 1000, 400);
  delay(220);
  tone(buzzerPin, 800, 200);
  delay(220);
  tone(buzzerPin, 1000, 400);
}

void Buzzers::initBuzzer(int pin){
  buzzerPin = pin;
  pinMode(buzzerPin, OUTPUT);
}

void Buzzers::playBeep() { // Sharp short beep for keypad
  tone(buzzerPin, 1800, 50); 
}

void Buzzers::playpetBeep() { // Sharp short beep for keypad
  tone(buzzerPin, 1500, 80); 
}
void Buzzers::playEQUALS() { // Sharp short beep for equals on 
  tone(buzzerPin, 1800, 50); 
  delay(100);
  tone(buzzerPin, 1800, 50); 
}

void Buzzers::playLevelUp() {
  for(int i = 0; i < 3; i++) {
    tone(buzzerPin, 1000 + (i * 200), 80); // increase pitch incrementally as if a level up instead of having multiple frequencies / tones
    delay(120);
  }
}

void Buzzers::playGameOver(){
  for(int i = 0; i < 4; i++) {
    tone(buzzerPin, 1000 - (i * 150), 250); // lower pitch incrementally for GameOver
    delay(270);
  }
}

void Buzzers::gameWinChime(){
  tone(buzzerPin, 1000, 400);
  delay(420);
  tone(buzzerPin, 1000, 100);
  delay(120);
  tone(buzzerPin, 1500, 600);
}
