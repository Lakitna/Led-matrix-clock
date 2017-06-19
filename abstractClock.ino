void abstractClock (byte mode) {
  for(byte i=1; i <= 12; i++) {
    for(int j=1; j <= 600; j++) {
      resetPixelArr();
      
      byte barWidth = 8;

      switch(mode) {
        case 1:
          if (i >= 10) {
            drawNumPixelArr(i, 3, 5, 2, 0); //big number
            //drawNumPixelArr(i, 5, 8, 1, 0); //small number
          } else {
            drawNumPixelArr(i, 8, 5, 2, 0); //big number
            //drawNumPixelArr(i, 9, 8, 1, 0); //small number
          }
          fillUp(j*5); // where max value 600*5 = 3000
        break;
        case 2:
          byte squareStart = (totalHorizontal / 2) - i;
          byte squareSize = i*2;
          
          drawSquarePixelArr(squareStart, squareStart, squareSize, squareSize);
          fillUp(j*5); // where max value 600*5 = 3000
        break;
      }

      matrixUpdate();
      scale();
      //debugPixelArr();
    }
  }
}

//Note: percentage where max = 3000 instead of 100.00
//      This is for optimisation reasons

float multiplier = totalPixels / 3000.0;
void fillUp (int percentage) {
  int fillPixels  = multiplier * percentage;
  int fullRows    = fillPixels / totalHorizontal;
  int loosePixels = fillPixels - (fullRows * totalHorizontal);

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
  for (int i=1; i <= fullRows; i++) {
    int y = totalVertical - i;
    
    for (int j=0; j < totalHorizontal; j++) {
      invertPixel(j,y);
    }
  }
  
  //Draw crawling horizontal line
  byte y = totalVertical - fullRows - 1;
  for (int j=0; j < loosePixels; j++) {
    invertPixel(j,y);
  }
}
