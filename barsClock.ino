void barsClock () {
  for (byte h=20; h < 24; h++) {
    for (byte m=0; m < 60; m++) {
      for (byte s=0; s < 60; s++) {
        resetPixelArr();
        Serial.print(h);
        Serial.print(":");
        Serial.print(m);
        Serial.print(":");
        Serial.println(s);
        
        for (byte x = 0; x < 12; x++) {
          for (byte y = 0; y < h; y++) {
            invertPixel(x, (y));
          }
        }
        for (byte x = 0; x < 7; x++) {
          for (byte y = 0; y < (m * 0.4); y++) {
            invertPixel((x+13), y);
          }
        }
        for (byte x = 0; x < 3; x++) {
          for (byte y = 0; y < (s * 0.4); y++) {
            invertPixel((x+21), y);
          }
        }
        
        matrixUpdate();
        delay(1000);
      }
    }
  }
}
