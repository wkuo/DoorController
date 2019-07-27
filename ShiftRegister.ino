



void writeSR(byte data) {
  digitalWrite(SR_LOAD, LOW);
  shiftOut(SR_DATA, SR_CLK, MSBFIRST, data); 
  digitalWrite(SR_LOAD, HIGH);
}

void testShiftReg() {
  byte data = B10000001;
  writeSR(data);
  delay(500);
  
  data = B01000010;
  writeSR(data);
  delay(500);
  
  data = B00100100;
  writeSR(data);
  delay(500);
}
