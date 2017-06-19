void drawNum (byte num, byte x, byte y, byte Size, boolean leadingZero) {
  if(num >= 10 || leadingZero == true) {
    byte numA = num/10;
    byte numB = num - (numA*10);

    if(Size == 2) {
      matrix.drawBitmap(x, y, bigNumArr[numA], 8, 14, 1);
      matrix.drawBitmap((x+9), y, bigNumArr[numB], 8, 14, 1);
    } else {
      matrix.drawBitmap(x, y, smallNumArr[numA], 6, 8, 1);
      matrix.drawBitmap((x+7), y, smallNumArr[numB], 6, 8, 1);
    }
  } else {
    if(Size == 2) {
      matrix.drawBitmap(x, y, bigNumArr[num], 8, 14, 1);
      //matrix.drawBitmap(x, y, font[num], 8, 14, 1);
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
        //drawPixel(x+i, y+j, color);
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
  if (pixelArr[y][x] == 0) {
    pixelArr[y][x] = 1;
  } else {
    pixelArr[y][x] = 0;
  }
}

void resetPixelArr () {
  for(byte i=0; i < totalVertical; i++) {
    for(byte j=0; j < totalHorizontal; j++) {
      pixelArr[i][j] = 0;
    }
  }
}

void debugPixelArr() {
  for(byte i=0; i < totalVertical; i++) {
    for(byte j=0; j < totalHorizontal; j++) {
      Serial.print(pixelArr[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println("-----------------------------------------------");
}

void matrixUpdate() {
  for(byte i=0; i < totalVertical; i++) {
    for(byte j=0; j < totalHorizontal; j++) {
      matrix.drawPixel(j, i, pixelArr[i][j]);
    }
  }
  matrix.write();
}

void scale() {
  switch(setScale) {
    case 0:
      delay(1); //Wait for 1ms, debugging
    break;
    case 1:
      delay(3000); //Wait for 3s, hour scale
    break;
    case 2:
      delay(90); //Wait for 90ms, minute scale
    break;
  }
}
