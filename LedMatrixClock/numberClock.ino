void numberClock(TimeKeeper t) {
  matrix.fillScreen(LOW);
  
  drawNum(t.h(), 0, 0, 1, 1);  //6x8
  drawNum(t.m(), 7, 10, 2, 1); //8x14
  
  matrix.write();
}
