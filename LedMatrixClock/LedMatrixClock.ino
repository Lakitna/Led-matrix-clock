#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#include "TimeKeeper.h"
#include "fps.h"
#include "bitmaps.h"

// High level settings
byte intensity = 0;   // Set brightness [0-15]

#define CS 10 // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
#define DISPLAY_COUNT_HORIZONTAL 3
#define DISPLAY_COUNT_VERTICAL   3




Max72xxPanel matrix = Max72xxPanel(CS, DISPLAY_COUNT_HORIZONTAL, DISPLAY_COUNT_VERTICAL);

TimeKeeper Time;
fps FPS;

const byte totalHorizontal = DISPLAY_COUNT_HORIZONTAL * 8;
const byte totalVertical   = DISPLAY_COUNT_VERTICAL   * 8;
const int  totalPixels     = totalHorizontal * totalVertical;

// Pixel buffer array
boolean pixelArr[totalVertical][totalHorizontal] = {
  {1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
  {1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1}
};

void setup() {
  Serial.begin(115200);

  Serial.print(   F("Compiled: "));
  Serial.print(   F(__DATE__));
  Serial.print(   F(", "));
  Serial.println( F(__TIME__));

  matrix.setIntensity(intensity);

  // Set matrices to reflect real-life position
  matrix.setPosition(0, 0, 0);
  matrix.setPosition(1, 1, 0);
  matrix.setPosition(2, 2, 0);
  matrix.setPosition(3, 2, 1);
  matrix.setPosition(4, 1, 1);
  matrix.setPosition(5, 0, 1);
  matrix.setPosition(6, 0, 2);
  matrix.setPosition(7, 1, 2);
  matrix.setPosition(8, 2, 2);

  // Set matrices to reflect real-life rotation
  matrix.setRotation(0, 1);
  matrix.setRotation(1, 1);
  matrix.setRotation(2, 1);
  matrix.setRotation(3, 3);
  matrix.setRotation(4, 3);
  matrix.setRotation(5, 3);
  matrix.setRotation(6, 1);
  matrix.setRotation(7, 1);
  matrix.setRotation(8, 1);

  // Initialize matrix
  matrixUpdate();

  delay(1500); // Show splash screen
}

void loop() {
  Time.tick(); // Keep time
  
  if (FPS.newSecond()) { // If screen should be updated

//    numberClock( Time );
    abstractClock( Time, 1 );
//    abstractClock( Time, 2 );
//    barsClock( Time );
    

//    debugPixelArr(); // Dump pixel array in Serial monitor
    debugging(); // Debug vals in Serial monitor
  }

  FPS.tick( Time );     // FPS counter - tick(TimeKeeper t)
  FPS.throttle( 3, 1 ); // Throttle to target FPS - throttle(uint8_t fps_cap, uint8_t variance)
}




