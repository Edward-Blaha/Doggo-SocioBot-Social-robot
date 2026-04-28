/*-----------------------------------------------------------------------------------------------------*/
/*                   DisplayDriver.cpp file for audio control on the SocioBot project                  */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/

// DISPLAYDRIVER.CPP for DISPLAYDRIVER.H
#include "DisplayDriver.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
// ALL BITMAPS ARE LOCATED AT bitmapFaces.cpp, GENERATED BITMAP ARRAYS USING image2cpp at https://javl.github.io/image2cpp/ (images drawn by Edward Blaha)
int CS= 5;
int DC= 7;
int RST= 6;

static int lastStage = -1;
int stage = 0;

Adafruit_ST7789 tft = Adafruit_ST7789(&SPI, CS, DC, RST);  //initalise display CS, DC & RESET pins

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::beginDisplay(int MOSI, int SCK) {
  SPI.setTX(MOSI);
  SPI.setSCK(SCK);
  SPI.begin();
  SPI.beginTransaction(SPISettings(60000000, MSBFIRST, SPI_MODE0)); //adjust clock speed to reduce flicker
  delay(3);            //buffer delay
  tft.init(240, 320);  //display size
  tft.setRotation(2);  // setting orientation relative to build.
  tft.setTextColor(ST77XX_WHITE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::printChar(char text) {
  tft.print(text);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::textSize(int input){
  tft.setTextSize(input);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::printCharln(char text) {
  tft.println(text);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::printString(const char* text) {
  tft.print(text);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::setprintln(int xShiftVal, int lineVal) {
  // Line 1 starts at 0, Line 2 at 20, Line 3 at 40, etc.
  int yCoordinate = (lineVal - 1) * 20; 
  tft.setCursor(xShiftVal, yCoordinate);// tft.setCursor(x, y)
  // set xShiftVal to 0 to have text all the way to the left
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::testScreen() {  // DEBUG && SCREEN RESET ONLY
  tft.fillScreen(ST77XX_RED);
  delay(700);
  tft.fillScreen(ST77XX_GREEN);
  delay(700);
  tft.fillScreen(ST77XX_BLUE);
  delay(700);
  tft.setRotation(2);
  clearScreen();
  for(int i = 0; i<100; i++){
    printString(String(i).c_str());
    delay(10);
  }
  delay(500);
  clearScreen();
  tft.drawBitmap(0, 0, bitmap_HappyFace, 240, 147, ST77XX_WHITE);
  delay(300);
  tft.setRotation(1);
  clearScreen();
  tft.drawBitmap(0, 0, bitmap_HappyFace, 240, 147, ST77XX_WHITE);
  delay(300);
  tft.setRotation(0);
  clearScreen();
  tft.drawBitmap(0, 0, bitmap_HappyFace, 240, 147, ST77XX_WHITE);
  delay(300);
  tft.setRotation(2);
  clearScreen();
  delay(100);
  tft.fillScreen(ST77XX_RED);
  delay(100);
  tft.fillScreen(ST77XX_GREEN);
  delay(100);
  tft.fillScreen(ST77XX_BLUE);
  delay(100);  // IF TEST FAILS, RESET SYSTEM VIA PHYSICAL RESET BUTTON!
  clearScreen();
  displayHappyFace();
  homeMenu();
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::resetBoredSequence() {
  lastStage = -1;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::displayHappyFace() {
  tft.drawBitmap(0, 0, bitmap_HappyFace, 240, 147, ST77XX_WHITE);  //ST77XX_WHITE due to the colour scheme of the image!
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::displayEstaticFace(){
  tft.drawBitmap(0, 0, bitmap_EstaticFace, 240, 147, ST77XX_WHITE);
}

void DisplayDriver::displayBeingPetFace(){
  tft.drawBitmap(0, 0, bitmap_beingPetFace, 240, 147, ST77XX_WHITE);
}

void DisplayDriver::displayDizzyFace(){
  tft.drawBitmap(0, 0, bitmap_DizzyFace, 240, 147, ST77XX_WHITE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::displaySadFace() {
  tft.drawBitmap(0, 0, bitmap_SadFace, 240, 147, ST77XX_WHITE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

bool DisplayDriver::clearScreen() {
  tft.fillScreen(ST77XX_BLACK);
  return true;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

bool DisplayDriver::clearFaceSpace() {  // used to clear the area in which the face is drawn
  tft.fillRect(0, 0, 240, 147, ST77XX_BLACK);
  return true;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::displayBored0Face() {
  tft.drawBitmap(0, 0, bitmap_bored, 240, 147, ST77XX_WHITE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::displayBored1Face() {
  tft.drawBitmap(0, 0, bitmap_bored1, 240, 147, ST77XX_WHITE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::displayBored2Face() {
  tft.drawBitmap(0, 0, bitmap_bored2, 240, 147, ST77XX_WHITE);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::homeMenu(){
  displayHappyFace();
  setprintln(0,9);
  tft.setTextSize(3);
  printString(" HOME SCREEN");
  tft.setTextSize(2);
  setprintln(0,11);
  printString(" Hello There! :D");
  setprintln(0,12);
  printString(" Calculator = '*'");
  setprintln(0,13);
  printString(" MemoryGame = '#'");

}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

void DisplayDriver::displayBoredSequence(unsigned long boredStartTime) {
  unsigned long elapsed = millis() - boredStartTime;
  if (elapsed >= 9000) {
    clearFaceSpace();
    displayBored2Face();
  }
  else if (elapsed >= 6000) {
    clearFaceSpace();
    displayBored1Face();
  }
  else if (elapsed >= 3000) {
    clearFaceSpace();
    displayBored0Face();
  }
}


/*-------------------------------------------------------------------------------------------------------------------------------------------*/
