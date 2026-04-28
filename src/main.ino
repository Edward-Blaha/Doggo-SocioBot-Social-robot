/* ----------------------------------------------------------------------- */
//      This is V1.8.0 of the main .ino file for the SOCIOBOT project,     //
//                                                                         //
//      Main objective is to interact with humans through basic sensor     //
//       inputs, i.e, PIR, Distance, touch, and send back a 'emotive'      //
//           response, as well as include a calculator & memoryGame        //
//                                function                                 // 
//                    Design and code by Edward Blaha                      //
//                                                                         //
//           Dedicated to the public domain via The Unlicense.             //
//                  See https://unlicense.org/ for details.                //
//                                                                         //
//                         Design by Edward Blaha                          //
//         For more information about this project, please visit           // 
//                     https://github.com/Edward-Blaha                     //
/*-------------------------------------------------------------------------*/
#include "DisplayDriver.h"
#include "Sensors.h"
#include "KeypadFunction.h"
#include "Calculator.h"
#include "MemoryGame.h"
#include "Buzzers.h"
MemoryGame myGame;
DisplayDriver tftDisplay;
Sensors sensor;

KeypadDef keypadDef = {
  {13,18,17,15},
  {14,12,16}
};
KeypadFunction myKeys(&keypadDef);
Calculator myCalculator;
Buzzers commBuzzer;
//
char key;
//
unsigned long lastActivityTime = 0;
bool hasActivity;
unsigned long boredStartTime = 0;
bool currentlyBored = false;
bool boredCycleDone;
//

bool isInCalculatorMode = false;
volatile bool endCalculator = false;
bool isInGameMode = false;
//
int buttonPin = 10;
volatile unsigned long lastButtonPressTime = 0; // Shared timer
const unsigned long debounceDelay = 100;       // 200ms threshold
//
int eggStep = 0;
bool hasBeenPet = false;
static bool petEffectTriggered = false; // 'static' remembers the value between loops
//
// int baseMagY = 0; // FOR FUTURE PROGRESS! COULD NOT GET IT TO WORK!
// int previousBaseMagneto = 0; // FOR FUTURE PROGRESS! COULD NOT GET IT TO WORK!
// const int pickUpThreshold = 120; // FOR FUTURE PROGRESS! COULD NOT GET IT TO WORK!
//

/*--------------------------------------------------------------------------------------*/

//Calculator and menu RESET / home button
void resetbuttonISR() {
  unsigned long currentTime = millis();
  if (currentTime - lastButtonPressTime > debounceDelay) {
    endCalculator = true; // This acts as "Home" / "RESET" signal ( Does not use physical reset pin on RP2040! )
    lastButtonPressTime = currentTime;
  }
}
/*--------------------------------------------------------------------------------------*/
// int magnetometerCheck() { // FOR FUTURE PROGRESS! COULD NOT GET IT TO WORK!
//   return sensor.readMagnetometer('y');
// }
/*--------------------------------------------------------------------------------------*/
// bool isPickedUp() { // FOR FUTURE PROGRESS! COULD NOT GET IT TO WORK!
//   int currentMagY = magnetometerCheck();
//   Serial.println(currentMagY);
//   int difference = abs(currentMagY - baseMagY);
//   return (difference > pickUpThreshold);
// }

/*--------------------------------------------------------------------------------------*/

void EasterEgg(char key) { //Easter egg can be activated if '1', '2', and '3' are pressed one after the other, AND ONLY IF NO OTHER FUNCTION IS RUNNING!
  if (!key) return; // Exit if no key was pressed

  // Step-by-step check
  if (eggStep == 0 && key == '1' && !isInCalculatorMode && !isInGameMode) {
    eggStep = 1; // Good start!
  } 
  else if (eggStep == 1 && key == '2' && !isInCalculatorMode && !isInGameMode) {
    eggStep = 2; // Almost there...
  } 
  else if (eggStep == 2 && key == '3' && !isInCalculatorMode && !isInGameMode) {
    tftDisplay.testScreen(); // Success!
    eggStep = 0;             // Reset
  } 
  else {
    eggStep = 0; // Wrong key pressed, start over!
  }
}

// check, is there activity?
bool isThereActivity(){
  if(sensor.readPIR() || sensor.readDistance() < 700 || sensor.touchSensorStatus()){ // If any sort of activity ? save time since last active and return true : return false
    lastActivityTime = millis();
    return true; // THERE IS ACTIVITY!
  } 
  return false;
}

/*--------------------------------------------------------------------------------------*/
// MEMORY GAME

void memoryGameSequence() {

  if (isInGameMode) {
    if (myGame.isActive()){
      myGame.handleInput(key, tftDisplay);
    } else {
      isInGameMode = false;
    }
  }
  else {
    // Switch to Game Mode with '#'
    if (key == '#' && !isInGameMode && !isInCalculatorMode) {
      isInGameMode = true;
      // myGame.start(tftDisplay);
    }
  }
}

/*--------------------------------------------------------------------------------------*/

// BORED SEQUENCE
void BoredSequence(){
  if(!isInCalculatorMode && !isInGameMode){
    if (hasActivity && currentlyBored) {//Transitioning from BORED back to ACTIVE due to sensor input
      currentlyBored = false;
      tftDisplay.clearFaceSpace();
      tftDisplay.displayEstaticFace();
      tftDisplay.setprintln(2, 9);
      tftDisplay.textSize(3);
      tftDisplay.printString("Hello Again!");
      commBuzzer.playLevelUp();
      Serial.println("Welcome back! Displaying Happy Face."); // debug
      delay(2000);
    }

    //Currently ACTIVE
    if (hasActivity) {
      lastActivityTime = millis(); // Keep resetting the timer while active
      currentlyBored = false; 
    } 
    
    //NO ACTIVITY - check if sociobot should enter BORED mode
    else if (millis() - lastActivityTime >= 15000) {
      if (!currentlyBored) {
        tftDisplay.clearScreen(); // Clear once when entering bored mode
        boredStartTime = millis();
        currentlyBored = true;
      }
      tftDisplay.displayBoredSequence(boredStartTime);
    }
  }
}

/*--------------------------------------------------------------------------------------*/

void calculateSequence() {
  //Check if '*' is pressed to enter mode
  if (key == '*' && !isInCalculatorMode) {
    isInCalculatorMode = true;
    tftDisplay.textSize(2);
    isInGameMode = false;  // Ensure we aren't in game mode
    tftDisplay.clearScreen();
    delay(10);
    tftDisplay.setprintln(1,2);
    tftDisplay.printString("Calculator Mode");
    tftDisplay.setprintln(1,3);
    myCalculator.reset(); 
    return; // Stop here so the '*' isn't processed as a number/math symbol
  }
  if(key == '#' && isInCalculatorMode){
    commBuzzer.playEQUALS();
  }

  //RESET, Check the hardware button signal
  if (endCalculator) {
    endCalculator = false;
    isInCalculatorMode = false;
    currentlyBored = false;
    myCalculator.reset(); 
    lastActivityTime = millis();
    Serial.println("System Reset: Returned to Home Screen");
  }

  //Only run if mode is active
  if (isInCalculatorMode) {
    myCalculator.run(key); 
  }
}

/*--------------------------------------------------------------------------------------*/

bool isBeingPet(){
  if(sensor.touchSensorStatus() && hasActivity){
    return true;
  }
  else{
    return false;
  }
}
//--------------------------------------------------MAIN LOOPS--------------------------------------------------------------//

void setup() { // Main code
  Serial.begin(115200); // debug only! (possibly for comms later!) 
  sensor.initSensors(8,9,0,1);
  myKeys.begin(); 
  pinMode(buttonPin, INPUT_PULLUP); // no need for external resistor
  attachInterrupt(digitalPinToInterrupt(buttonPin), resetbuttonISR , FALLING); // for reset button
  tftDisplay.beginDisplay(3,2); //Pin define for display (SPI)
  commBuzzer.initBuzzer(11); //buzzer pin init
  commBuzzer.powerOnChime();
  tftDisplay.clearScreen();
  hasActivity = false; 
  tftDisplay.displayHappyFace();
  tftDisplay.textSize(2);
  tftDisplay.setprintln(1,2);
  delay(30);
  // baseMagY = sensor.readMagnetometer('y'); // FOR FUTURE PROGRESS! COULD NOT GET IT TO WORK!
  // previousBaseMagneto = baseMagY;
  
}

int lastState = -1; // 0=Home, 1=Calc, 2=Game, 3=Bored, 4=Pet, 5= magnetometer change

void loop() {
  myKeys.tick();
  hasActivity = isThereActivity();
  key = myKeys.getPressedKey();
  
  if(key) commBuzzer.playBeep();

  // 1. DETERMINE THE CURRENT STATE
  int currentState;
  // if (isPickedUp())              currentState = 5; // Magnetometer trigger takes priority        // FOR FUTURE PROGRESS! COULD NOT GET IT TO WORK!
  if (isInCalculatorMode)   currentState = 1;
  else if (isInGameMode)         currentState = 2;
  else if (currentlyBored)       currentState = 3;
  else if (isBeingPet())         currentState = 4;
  else                           currentState = 0; // Default: Home

  if (currentState != lastState) {
    tftDisplay.clearScreen(); 

    switch (currentState) {
      case 0: // HOME
        tftDisplay.textSize(1);
        tftDisplay.displayHappyFace();
        tftDisplay.homeMenu();
        break;

      case 1: // CALCULATOR
        tftDisplay.textSize(2);
        tftDisplay.setprintln(1, 2);
        tftDisplay.printString("Calculator Mode");
        myCalculator.reset();
        break;

      case 2: // GAME
        tftDisplay.textSize(2);
        tftDisplay.setprintln(1, 2);
        tftDisplay.printString("Starting Game...");
        delay(1000); // Shortened delay for better feel
        myGame.start(tftDisplay);
        break;

      case 3: // BORED
        boredStartTime = millis();
        break;

      case 4: // PETTING
        tftDisplay.displayEstaticFace(); // Using your existing face method
        commBuzzer.playBeep();
        break;
        
      // case 5: // DIZZY / PICKED UP         // FOR FUTURE PROGRESS! COULD NOT GET IT TO WORK!
      //   tftDisplay.displayDizzyFace();
      //   commBuzzer.playEQUALS(); 
      //   break;
    }
    lastState = currentState; 
  }

  // 3. RUN CONSTANT LOGIC
  BoredSequence();
  calculateSequence();
  memoryGameSequence();
  EasterEgg(key);
  
  // Update tracking variable for the next loop
  // previousBaseMagneto = magnetometerCheck(); // FOR FUTURE PROGRESS! COULD NOT GET IT TO WORK!
}


