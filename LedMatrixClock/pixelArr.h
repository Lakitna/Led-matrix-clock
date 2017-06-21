class pixelArr {
  byte totalVertical;
  byte totalHorizontal;
  
  boolean buffer[ DISPLAY_COUNT_VERTICAL*8 ][ DISPLAY_COUNT_HORIZONTAL*8 ];
  
  
  public:
    pixelArr(byte w, byte h) {
      totalVertical = h;
      totalHorizontal = w;


const byte totalHorizontal = DISPLAY_COUNT_HORIZONTAL * 8;
const byte totalVertical   = DISPLAY_COUNT_VERTICAL   * 8;
const int  totalPixels     = totalHorizontal * totalVertical;

Max72xxPanel matrix = Max72xxPanel(CS, DISPLAY_COUNT_HORIZONTAL, DISPLAY_COUNT_VERTICAL);
pixelArr matrixArr(CS, DISPLAY_COUNT_HORIZONTAL, DISPLAY_COUNT_VERTICAL);


      boolean buffer[w][h] = {
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
      
    }

    void invertPixel (byte x, byte y) {
      buffer[y][x] = !buffer[y][x];
    }


    void write() {
      for(byte y=0; y < totalVertical; y++) {
        for(byte x=0; x < totalHorizontal; x++) {
          matrix.drawPixel(x, y, buffer[y][x]);
        }
      }
      matrix.write();
    }
  
};
