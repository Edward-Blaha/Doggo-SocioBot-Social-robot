/*-----------------------------------------------------------------------------------------------------*/
/*                     Calculator.cpp file for audio control on the SocioBot project                   */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/

#include <Arduino.h>
#include "Calculator.h"

// Global calculator state
long long result;
long long currentNumber;
char op;
int counterI;
Calculator::Calculator() {
    // Main constructor
    state = ENTER_NUMBER;
    result = 0;
    currentNumber = 0;
    op = '+';
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void Calculator::calculate() {
  switch (op) {
    case '+': 
      result += currentNumber; 
      break;
    case '-': 
      result -= currentNumber; 
      break;
    case '*': 
      result *= currentNumber; 
      break;
    case '/': 
      if (currentNumber != 0) {  // Safe division
        result /= currentNumber;
      }
      break;
  }
  currentNumber = 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void Calculator::run(char key) {
  if (!key) return;

  // 1. NUMBER HANDLING
  if (key >= '0' && key <= '9') {
    currentNumber = currentNumber * 10 + (key - '0');
    tftDisplay.printChar(key); 
  }

  // 2. THE OPERATOR CYCLE (*)
  else if (key == '*') {
    // ONLY calculate if the user has typed a number since the last operator
    // This prevents the '0' reset from wiping your result when cycling
    if (currentNumber != 0) {
        calculate(); 
    }
    
    // Cycle the operator
    if (op == '+') op = '-';
    else if (op == '-') op = '*';
    else if (op == '*') op = '/';
    else op = '+';

    // UI: Overwrite or indicate the new operator
    tftDisplay.printChar(' ');
    tftDisplay.printChar(op); 
    tftDisplay.printChar(' ');
  }

  // 3. THE EQUALS KEY (#)
  else if (key == '#') {
    calculate(); // Final calculation
    tftDisplay.printChar('=');
    tftDisplay.printString(String(result).c_str());
    result = 0;        // Reset the running total so the next sum starts at 0
    currentNumber = 0; // Reset the current input
    op = '+';          // Reset the operator
    counterI++;
    tftDisplay.setprintln(0,3+counterI);
    if(counterI == 10){
      counterI = 0;
      tftDisplay.clearScreen();
      tftDisplay.setprintln(1,2);
      tftDisplay.printString("Calculator Mode");
      tftDisplay.setprintln(1,3);
    }
    
    currentNumber = 0; 
  }
}


void Calculator::reset() {
  result = 0;
  currentNumber = 0;
  op = '+';
  state = ENTER_NUMBER;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
