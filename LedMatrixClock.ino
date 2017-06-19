#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

byte intensity = 0;   // Set brightness [0-15]
byte setScale = 0;       // 0 = debug, 1 = hour, 2 = minute

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
const byte numberOfHorizontalDisplays = 3;
const byte numberOfVerticalDisplays = 3;
const byte totalHorizontal = numberOfHorizontalDisplays * 8;
const byte totalVertical   = numberOfVerticalDisplays   * 8;
const int totalPixels = totalHorizontal * totalVertical;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

boolean pixelArr[totalVertical][totalHorizontal] = {
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
  {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
  {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
  {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
  {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0},
  {0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0},
  {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
  {0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0},
  {0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
  {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
  {0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0},
  {0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0},
  {0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1}
};

// 8x14 numbers
static const unsigned char PROGMEM bigOne[] = { 0x18, 0x38, 0x78, 0xd8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0xff, };
static const unsigned char PROGMEM bigTwo[] = { 0x3c, 0x7e, 0xe7, 0xc3, 0x3, 0x3, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc0, 0xff, 0xff, };
static const unsigned char PROGMEM bigThr[] = { 0x3c, 0x7e, 0xe7, 0xc3, 0x3, 0x7, 0x1e, 0x1e, 0x7, 0x3, 0xc3, 0xe7, 0x7e, 0x3c, };
static const unsigned char PROGMEM bigFou[] = { 0x6, 0xe, 0xe, 0x1e, 0x16, 0x36, 0x26, 0x66, 0x46, 0xff, 0xff, 0x6, 0x6, 0x6,  };
static const unsigned char PROGMEM bigFiv[] = { 0xfe, 0xfe, 0xc0, 0xc0, 0xc0, 0xfc, 0xfe, 0xc7, 0x3, 0x3, 0x3, 0xe7, 0x7e, 0x3c, };
static const unsigned char PROGMEM bigSix[] = { 0x3c, 0x7e, 0xe0, 0xc0, 0xc0, 0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c, };
static const unsigned char PROGMEM bigSev[] = { 0xff, 0xff, 0x3, 0x6, 0xc, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, };
static const unsigned char PROGMEM bigEig[] = { 0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0x66, 0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c, };
static const unsigned char PROGMEM bigNin[] = { 0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0x7f, 0x3b, 0x3, 0x3, 0x7, 0x7e, 0x3c, };
static const unsigned char PROGMEM bigZer[] = { 0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c,  };
const unsigned char* bigNumArr[] = { bigZer, bigOne, bigTwo, bigThr, bigFou, bigFiv, bigSix, bigSev, bigEig, bigNin };

// 6x8 numbers
static const unsigned char PROGMEM smallOne[] = { 0x10, 0x30, 0x70, 0x30, 0x30, 0x30, 0x78, 0x78, };
static const unsigned char PROGMEM smallTwo[] = { 0x78, 0xfc, 0x8c, 0x18, 0x30, 0x60, 0xfc, 0xfc, };
static const unsigned char PROGMEM smallThr[] = { 0x78, 0xfc, 0x8c, 0x38, 0x38, 0x8c, 0xfc, 0x78, };
static const unsigned char PROGMEM smallFou[] = { 0x18, 0x38, 0x78, 0xd8, 0xfc, 0xfc, 0x18, 0x18, };
static const unsigned char PROGMEM smallFiv[] = { 0xfc, 0xfc, 0xc0, 0xf8, 0xfc, 0xc, 0xfc, 0xf8, };
static const unsigned char PROGMEM smallSix[] = { 0x78, 0xfc, 0xc0, 0xf8, 0xfc, 0xcc, 0xfc, 0x78, };
static const unsigned char PROGMEM smallSev[] = { 0xfc, 0xfc, 0x8, 0x18, 0x18, 0x18, 0x18, 0x18, };
static const unsigned char PROGMEM smallEig[] = { 0x78, 0xfc, 0xcc, 0xfc, 0xfc, 0xcc, 0xfc, 0x78, };
static const unsigned char PROGMEM smallNin[] = { 0x78, 0xfc, 0xcc, 0xfc, 0x7c, 0xc, 0xfc, 0x78, };
static const unsigned char PROGMEM smallZer[] = { 0x78, 0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xfc, 0x78, };
const unsigned char* smallNumArr[] = { smallZer, smallOne, smallTwo, smallThr, smallFou, smallFiv, smallSix, smallSev, smallEig, smallNin };

void setup() {
  Serial.begin(57600);
  matrix.setIntensity(intensity);
  
  matrix.setPosition(0, 0, 0);
  matrix.setPosition(1, 1, 0);
  matrix.setPosition(2, 2, 0);
  matrix.setPosition(3, 2, 1);
  matrix.setPosition(4, 1, 1);
  matrix.setPosition(5, 0, 1);
  matrix.setPosition(6, 0, 2);
  matrix.setPosition(7, 1, 2);
  matrix.setPosition(8, 2, 2);

  matrix.setRotation(0, 1);
  matrix.setRotation(1, 1);
  matrix.setRotation(2, 1);
  matrix.setRotation(3, 3);
  matrix.setRotation(4, 3);
  matrix.setRotation(5, 3);
  matrix.setRotation(6, 1);
  matrix.setRotation(7, 1);
  matrix.setRotation(8, 1);

  matrixUpdate();
  delay(1000);
}

void loop() {
  matrix.setIntensity(intensity);
  
  //numberClock();
  //abstractClock(1);
  //abstractClock(2);
  barsClock();
}

