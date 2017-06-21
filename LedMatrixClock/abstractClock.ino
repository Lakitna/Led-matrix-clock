void abstractClock(TimeKeeper t, byte mode) {
  resetPixelArr();
  
  switch(mode) {
    case 1:
      if (t.h(12) >= 10) {
        drawNumPixelArr(t.h(12), 3, 5, 2, false); //big number
      } else {
        drawNumPixelArr(t.h(12), 8, 5, 2, false); //big number
      }
      fillUp( (t.m() * 60) + t.s() ); // where max value 3600
    break;
    case 2:
      // From 24 to 12 hour clock
      byte h = t.h(12);

      byte squareStart = (totalHorizontal / 2) - h;
      byte squareSize  = h * 2;
      
      drawSquarePixelArr(squareStart, squareStart, squareSize, squareSize);
      fillUp( (t.m() * 60) + t.s() ); // where max value 3600
    break;
  }

  matrixUpdate();
}

//Note: percentage where max = 3600 instead of 100.00
//      This is for optimisation reasons
float multiplier = totalPixels / 3600.0;
void fillUp (int percentage) {
  int  fillPixels  = multiplier * percentage;
  byte fullRows    = fillPixels / totalHorizontal;
  byte loosePixels = fillPixels - (fullRows * totalHorizontal);

  //Draw full horizontal lines
  for (byte i=1; i <= fullRows; i++) {
    byte y = totalVertical - i;
    
    for (byte j=0; j < totalHorizontal; j++) {
      invertPixel(j,y);
    }
  }
  
  //Draw crawling horizontal line
  for (byte j=0; j < loosePixels; j++) {
    invertPixel(j, (totalVertical - fullRows - 1));
  }
}
