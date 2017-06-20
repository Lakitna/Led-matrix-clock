void abstractClock(TimeKeeper t, byte mode) {
  resetPixelArr();
  
  switch(mode) {
    case 1:
      if (t.h() >= 10) {
        drawNumPixelArr(t.h(), 3, 5, 2, 0); //big number
        //drawNumPixelArr(i, 5, 8, 1, 0); //small number
      } else {
        drawNumPixelArr(t.h(), 8, 5, 2, 0); //big number
        //drawNumPixelArr(i, 9, 8, 1, 0); //small number
      }
      fillUp( (t.m() * 60) + t.s() ); // where max value 3600
    break;
    case 2:
      byte squareStart = (totalHorizontal / 2) - t.h();
      byte squareSize  = t.h() * 2;
      
      drawSquarePixelArr(squareStart, squareStart, squareSize, squareSize);
      fillUp( (t.m() * 60) + t.s() ); // where max value 3600
    break;
  }

  matrixUpdate();
  //debugPixelArr();
}

//Note: percentage where max = 3600 instead of 100.00
//      This is for optimisation reasons

float multiplier = totalPixels / 3600.0;
void fillUp (int percentage) {
  int  fillPixels  = multiplier * percentage;
  byte fullRows    = fillPixels / totalHorizontal;
  byte loosePixels = fillPixels - (fullRows * totalHorizontal);

/*
  Serial.print("percentage: ");
  Serial.print(percentage);
  Serial.print("\t totalPixels: ");
  Serial.print(totalPixels);
  Serial.print("\t fillPixels: ");
  Serial.print(fillPixels);
  Serial.print("\t fullRows: ");
  Serial.println(fullRows);
*/

  //Draw full horizontal lines
  for (byte i=1; i <= fullRows; i++) {
    byte y = totalVertical - i;
//    int y = i-1;
    
    for (byte j=0; j < totalHorizontal; j++) {
      invertPixel(j,y);
    }
  }
  
  //Draw crawling horizontal line
  byte y = totalVertical - fullRows - 1;
  for (byte j=0; j < loosePixels; j++) {
    invertPixel(j,y);
  }
}
