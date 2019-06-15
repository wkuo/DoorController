

// Motor A is door
void motorAStop() {
  //delay(delayA);//why required?
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void motorAForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //analogWrite(enA, maxSpeedA); 
  //motorAStop(); // think this is reason for jerking
}

void motorABackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, maxSpeedA);
  //motorAStop(); // think this is reason for jerking  
}

void motorBStop() {
  //delay(delayB);//why required?
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void motorBForward() {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, maxSpeedB); 
  //while (stateB!=2) {
  //  analogRead(sensorB1);
  //}
  
  //motorBStop();//// think this is reason for jerking
}

void motorBBackward() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, maxSpeedB); 
  //motorBStop();// think this is reason for jerking
}


