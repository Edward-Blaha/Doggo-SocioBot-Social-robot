/*-----------------------------------------------------------------------------------------------------*/
/*                      Calculator.h file for audio control on the SocioBot project                    */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/


#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <Arduino.h>
#include "KeypadFunction.h"
#include "DisplayDriver.h"

extern DisplayDriver tftDisplay;

class Calculator {
  public:
  Calculator();           // constructor
  void run(char key);             // main calculator logic
  void reset();
  private:
  long result;
  long currentNumber;
  char op;
  // DisplayDriver tftDisplay;

  enum CalcState {
    ENTER_NUMBER,
    ENTER_OPERATOR
  };
  CalcState state;
  void calculate();
};
#endif
