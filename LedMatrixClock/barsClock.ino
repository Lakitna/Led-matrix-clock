void barsClock(TimeKeeper t) {
  resetPixelArr();
  
  for (byte x = 0; x < 12; x++) {
    for (byte y = 0; y < t.h(); y++) {
      invertPixel(x, (y));
    }
  }
  for (byte x = 0; x < 7; x++) {
    for (byte y = 0; y < (t.m() * 0.4); y++) {
      invertPixel((x+13), y);
    }
  }
  for (byte x = 0; x < 3; x++) {
    for (byte y = 0; y < (t.s() * 0.4); y++) {
      invertPixel((x+21), y);
    }
  }
  
  matrixUpdate();
}
