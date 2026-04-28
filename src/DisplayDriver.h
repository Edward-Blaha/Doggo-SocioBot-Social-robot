/*-----------------------------------------------------------------------------------------------------*/
/*                             DisplayDriver.cpp file on the SocioBot project                          */
/*                            Dedicated to the public domain via The Unlicense.                        */
/*                              See https://unlicense.org/ for details.                                */
/*                                                                                                     */
/*                                      Design by Edward Blaha                                         */
/*         For more information about this project, please visit https://github.com/Edward-Blaha       */
/*-----------------------------------------------------------------------------------------------------*/

/* 2.0 inch TFT display driver Library, utilising the Adafruit_ST7789 library*/
#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H
#include <Arduino.h> // Weird error found during compilation, Documentation rules out issue.
// ALL BITMAP DECLARATIONS!
extern const unsigned char bitmap_EstaticFace[]; // Array of EstaticFace bitmap
extern const unsigned char bitmap_HappyFace[]; // Array of HappyFace bitmap
extern const unsigned char bitmap_SadFace[]; // Array of SadFace bitmap
extern const unsigned char bitmap_DizzyFace []; // Array of DizzyFace bitmap
extern const unsigned char bitmap_beingPetFace []; // Array of beingPetFace bitmap
extern const unsigned char bitmap_bored []; // Array of bored frame 1/3 bitmap
extern const unsigned char bitmap_bored1 []; // Array of bored frame 2/3 bitmap
extern const unsigned char bitmap_bored2 []; // Array of bored frame 3/3 bitmap

class DisplayDriver{  
  public:
  void beginDisplay(int MOSI, int SCK);
  void displayHappyFace();
  void displayEstaticFace();
  void displaySadFace();
  void displayBeingPetFace();
  void displayDizzyFace();
  void displayBored0Face();
  void displayBored1Face();
  void displayBored2Face();
  void displayBoredSequence(unsigned long boredStartTime);
  /*debug*/
  void testScreen();
  /*----*/
  bool clearScreen();
  bool clearFaceSpace();
  void printChar(char text);
  void printCharln(char text);
  void setprintln(int xShiftVal, int lineVal);
  void printString(const char* text);
  void resetBoredSequence();
  void homeMenu();
  void textSize(int input);
};

#endif
