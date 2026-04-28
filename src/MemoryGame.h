/*-----------------------------------------------------------------------------------------------------*/
/*                      MemoryGame.h file for Game Function on the SocioBot project                    */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/

#ifndef MEMORYGAME_H
#define MEMORYGAME_H

#include <Arduino.h>
#include "DisplayDriver.h"
#include "Buzzers.h"

static const int MAX_MEMORY_SEQ_LEN = 5;

class MemoryGame {
public:
  MemoryGame();
  void start(DisplayDriver &display); // using & display so I do not have to redefine again
  void handleInput(char key, DisplayDriver &display);
  bool isActive() { return gameActive; }
  Buzzers gameBuzzer;

private:
  int sequence[MAX_MEMORY_SEQ_LEN]; // (max sequence the game can have)
  int currentLevel;
  int inputStep;
  bool gameActive;
  bool showingSequence;
    
  void nextLevel(DisplayDriver &display);
  void winScreen(DisplayDriver &display);
  void playSequence(DisplayDriver &display);
};

#endif
