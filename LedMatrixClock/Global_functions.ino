void debugging() {
  Serial.print(Time.h());
  Serial.print(":");
  Serial.print(Time.m());
  Serial.print(":");
  Serial.print(Time.s());

  Serial.print(" \tFPS: ");
  Serial.print(FPS.get());
    
  Serial.println();
}




void drawNum(byte num, byte x, byte y, byte size, boolean leadingZero) {
  if(num >= 10 || leadingZero == true) {
    byte numA = num/10;
    byte numB = num - (numA*10);

    if(size == 2) {
      matrix.drawBitmap(x, y, bigNumArr[numA], 8, 14, 1);
      matrix.drawBitmap((x+9), y, bigNumArr[numB], 8, 14, 1);
    } else {
      matrix.drawBitmap(x, y, smallNumArr[numA], 6, 8, 1);
      matrix.drawBitmap((x+7), y, smallNumArr[numB], 6, 8, 1);
    }
  } else {
    if(size == 2) {
      matrix.drawBitmap(x, y, bigNumArr[num], 8, 14, 1);
    } else {
      matrix.drawBitmap(x, y, smallNumArr[num], 6, 8, 1);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
void drawNumPixelArr(byte num, byte x, byte y, byte Size, boolean leadingZero) {
  if(num >= 10 || leadingZero == true) {
    byte numA = num / 10;
    byte numB = num - (numA*10);

    if(Size == 2) {
      drawBitmapPixelArr(x, y, bigNumArr[numA], 8, 14);
      drawBitmapPixelArr((x+10), y, bigNumArr[numB], 8, 14);
    } else {
      drawBitmapPixelArr(x, y, smallNumArr[numA], 6, 8);
      drawBitmapPixelArr((x+7), y, smallNumArr[numB], 6, 8);
    }
  } else {
    if(Size == 2) {
      drawBitmapPixelArr(x, y, bigNumArr[num], 8, 14);
    } else {
      drawBitmapPixelArr(x, y, smallNumArr[num], 6, 8);
    }
  }
}

void drawBitmapPixelArr(byte x, byte y, const uint8_t *bitmap, byte w, byte h) {
  int16_t byteWidth = (w + 7) / 8;
  
  for(byte j=0; j<h; j++) {
    for(byte i=0; i<w; i++) {
      if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
        invertPixel(x+i, y+j);
      }
    }
  }
} 

void drawSquarePixelArr (byte x, byte y, byte w, byte h) {
  //Horizontal top line
  for (byte i = x; i < (x + w); i++) {
    pixelArr[y][i] = 1;
  }
  //Horizontal bottom line
  for (byte i = x; i < (x + w); i++) {
    pixelArr[y+h-1][i] = 1;
  }
  //Vertical left line
  for (byte i = y; i < (y + h); i++) {
    pixelArr[i][x] = 1;
  }
  //Vertical right line
  for (byte i = y; i < (y + h); i++) {
    pixelArr[i][x+w-1] = 1;
  }
}

void invertPixel (byte x, byte y) {
  pixelArr[y][x] = !pixelArr[y][x];
}

void resetPixelArr () {
  memset(pixelArr, 0, totalPixels);
}

void debugPixelArr() {
  for(byte i=0; i < totalVertical; i++) {
    for(byte j=0; j < totalHorizontal; j++) {
      if (pixelArr[i][j]) Serial.print("O");
      else                Serial.print(" ");
//      Serial.print(pixelArr[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println("-----------------------------------------------");
}

void matrixUpdate() {
  for(byte y=0; y < totalVertical; y++) {
    for(byte x=0; x < totalHorizontal; x++) {
      matrix.drawPixel(x, y, pixelArr[y][x]);
    }
  }
  matrix.write();
}
