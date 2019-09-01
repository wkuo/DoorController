
void armStop() {
  Serial.println("Arm idle");
}

void armUp() {
  Serial.println("Arm Up");
}

void armDown() {
  Serial.println("Arm Down");
}



// Motor A is door
void motorAStop() {
  Serial.println("Door idle");
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, LOW);
//  analogWrite(enA, 0); 
}

void motorAForward(int motorspeed) {
  Serial.println("Door opening");
//  digitalWrite(in1, HIGH);
//  digitalWrite(in2, LOW);
//  analogWrite(enA, motorspeed);   
}

void motorABackward(int motorspeed) {
  Serial.println("Door closing");
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, HIGH);
//  analogWrite(enA, motorspeed);
}

void motorBStop() {
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, LOW);
//  analogWrite(enB, 0); 
}

void motorBForward(int motorspeed) {
//  digitalWrite(in3, HIGH);
//  digitalWrite(in4, LOW);
//  analogWrite(enB, motorspeed);
}

void motorBBackward(int motorspeed) {
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, HIGH);
//  analogWrite(enB, motorspeed);

}
