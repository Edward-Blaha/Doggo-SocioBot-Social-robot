/*-----------------------------------------------------------------------------------------------------*/
/*                               MemoryGame.h file on the SocioBot project                             */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/

#include "MemoryGame.h"

MemoryGame::MemoryGame() {
  gameActive = false;
  currentLevel = 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void MemoryGame::start(DisplayDriver &display) {
  gameActive = true;
  currentLevel = 1;
  inputStep = 0;
  randomSeed(millis()); // Use timing for almost true randomness
  nextLevel(display);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void MemoryGame::nextLevel(DisplayDriver &display) {
  if ( currentLevel > MAX_MEMORY_SEQ_LEN ) {
    winScreen(display);
    gameActive = false;
  }
  else {
    sequence[currentLevel - 1] = random(0, 10); // Pick 0-9
    playSequence(display);
  }
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void MemoryGame::winScreen(DisplayDriver &display) {
  display.clearScreen();
  display.displayEstaticFace();
  display.setprintln(1, 9);
  display.printString("YOU WIN!");
  gameBuzzer.gameWinChime();
  delay(2000); 
}

void MemoryGame::playSequence(DisplayDriver &display) { // POSSIBLY USE SOMETHING ELSE! MAYBE CHANGE TO millis(); LOGIC?
  display.clearScreen();
  display.setprintln(1, 2);
  display.printString("WATCH CAREFULLY!");
  delay(700);

  for (int i = 0; i < currentLevel; i++) {
    display.clearScreen();
    display.setprintln(2, 4); // Center of screen
    display.printString(String(sequence[i]).c_str());
    delay(500); 
    display.clearScreen();
    delay(200);
  }
  
  display.setprintln(1, 2);
  display.printString("YOUR TURN...");
  inputStep = 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void MemoryGame::handleInput(char key, DisplayDriver &display) {
  if (key < '0' || key > '9') return; // Only 0-9 count, else, check for condition again
  int pressed = key - '0'; // convert ASCII character to int
  
  if (pressed == sequence[inputStep]) {
    inputStep++;
    if (inputStep == currentLevel) {
      currentLevel++;
      display.clearScreen();
      display.setprintln(5,2);
      display.printString("CORRECT!");
      gameBuzzer.playLevelUp();
      display.setprintln(0,0);
      delay(1000);
      nextLevel(display);
    }
  } 
  else {
    // GAME OVER
    display.clearScreen();
    display.displaySadFace();
    display.setprintln(4, 9);
    display.printString("INCORRECT!");
    display.setprintln(4, 11);
    display.textSize(4);
    display.printString("GAME OVER");
    gameBuzzer.playGameOver();
    display.textSize(1);
    delay(3000);
    gameActive = false;
  }
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/
