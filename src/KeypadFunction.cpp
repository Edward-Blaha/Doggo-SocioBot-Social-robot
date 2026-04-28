/*-----------------------------------------------------------------------------------------------------*/
/*                   KeypadFunction.cpp file for input control on the SocioBot project                 */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/

#include "KeypadFunction.h"
#include <Arduino.h>
char keyMap[KEYPAD_ROWS][KEYPAD_COLS] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

KeypadFunction::KeypadFunction( KeypadDef* padDef )
  : mainKeypad(makeKeymap(keyMap), padDef->rowPins, padDef->colPins, KEYPAD_ROWS, KEYPAD_COLS )
{}

void KeypadFunction::begin() {
  mainKeypad.begin();
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void KeypadFunction::tick(){
  mainKeypad.tick();
}
/*-------------------------------------------------------------------------------------------------------------------------------------------*/

char KeypadFunction::getPressedKey(){
  char pressed = 0;
  while(mainKeypad.available()) {
    keypadEvent e = mainKeypad.read();
    delay(10);// BLOCKING DEBOUNCE!
    if(e.bit.EVENT == KEY_JUST_PRESSED) {
      pressed = (char)e.bit.KEY;
      Serial.printf("Pressed %c\n", pressed);
      
      break;
    }
  }
  return pressed;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

