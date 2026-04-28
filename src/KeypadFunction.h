/*-----------------------------------------------------------------------------------------------------*/
/*                   KeypadFunction.cpp file for input control on the SocioBot project                 */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/

#ifndef KEYPADFUNCTION_H
#define KEYPADFUNCTION_H

#include <Arduino.h>
#include <Adafruit_Keypad.h>

static const int KEYPAD_ROWS = 4;
static const int KEYPAD_COLS = 3;


struct KeypadDef {
  byte rowPins[KEYPAD_ROWS];
  byte colPins[KEYPAD_COLS];
};

class KeypadFunction{
public:
  KeypadFunction( KeypadDef* keypadDef );
  char getPressedKey();
  void begin();
  void tick();

private:
  Adafruit_Keypad mainKeypad;
  
};
#endif
