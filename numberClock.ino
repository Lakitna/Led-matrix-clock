void numberClock () {
  for(byte h=0; h<12; h++) {
    for(byte m=0; m<60; m++) {
      matrix.fillScreen(LOW);

      drawNum(h, 0, 0, 1, 1);  //6x8

      drawNum(m, 7, 10, 2, 1); //8x14

      matrix.write();
      //delay(60000); //Wait for 60 seconds, hour scale
      delay(1000); //Wait for 1 second, minute scale
    }
  }
}
