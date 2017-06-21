void debugging() {
  Serial.print(Time.h());
  Serial.print(":");
  Serial.print(Time.m());
  Serial.print(":");
  Serial.print(Time.s());

  Serial.print("   \tFPS: ");
  Serial.print(FPS.get());
    
  Serial.println();
}



void drawNumHelper(int num, byte x, byte y, byte size, boolean leadingZero, byte mode) {
  byte n;
  String numStr = String(num);
  byte charCount = numStr.length();
  
  byte* sizes;
  if (size == 1)
    sizes = smallNumSizes;
  else if (size == 2)
    sizes = bigNumSizes;

  // If leading zero should be added
  if (leadingZero && charCount == 1) {
    numStr = "0"+numStr;
    charCount++;
  }

  // Normal (library) mode
  if (mode == 0) {
    // For every character that should be printed
    for (byte c=0; c<charCount; c++) {
      n = numStr.substring(c, (c+1)).toInt();
  
      if (size == 1)
        matrix.drawBitmap((x+(c*(sizes[0]+sizes[2]))), y, smallNumArr[n], sizes[0], sizes[1], 1);
      else if (size == 2)
        matrix.drawBitmap((x+(c*(sizes[0]+sizes[2]))), y, bigNumArr[n],   sizes[0], sizes[1], 1);
    }
  }
  // Pixelarray invert pixel mode
  else if (mode == 1) {
    // For every character that should be printed
    for (byte c=0; c<charCount; c++) {
      n = numStr.substring(c, (c+1)).toInt();
  
      if (size == 1)
        drawBitmapPixelArr((x+(c*(sizes[0]+sizes[2]))), y, smallNumArr[n], sizes[0], sizes[1]);
      else if (size == 2)
        drawBitmapPixelArr((x+(c*(sizes[0]+sizes[2]))), y, bigNumArr[n],   sizes[0], sizes[1]);
    }
  }
}

void drawNum(int num, byte x, byte y, byte size, boolean leadingZero) {
  drawNumHelper(num, x, y, size, leadingZero, 0);
}

void drawNumPixelArr(byte num, byte x, byte y, byte size, boolean leadingZero) {
  drawNumHelper(num, x, y, size, leadingZero, 1);
}

void drawBitmapPixelArr(byte x, byte y, const uint8_t *bitmap, byte w, byte h) {
//  int16_t byteWidth = (w + 7) / 8;
  uint8_t byteWidth = (w + 7) / 8;
  
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
    invertPixel(y, i);
  }
  //Horizontal bottom line
  for (byte i = x; i < (x + w); i++) {
    invertPixel(y+h-1, i);
  }
  //Vertical left line
  for (byte i = y+1; i < (y + h -1); i++) {
    invertPixel(i, x);
  }
  //Vertical right line
  for (byte i = y+1; i < (y + h -1); i++) {
    invertPixel(i, x+w-1);
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
