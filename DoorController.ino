#include <YK04_Module.h>

#define A_PIN  12
#define B_PIN  10
#define C_PIN  13
#define D_PIN  11  
#define NEAR_PIN 2

YK04_Module* module;
// Motor A
int enA = 9;
int in1 = 8;
int in2 = 7;
int maxSpeedA = 200;
 
// Motor B 
int enB = 3;
int in3 = 5;
int in4 = 4;
int maxSpeedB = 200;

void setup() { 
  delay(500);
  Serial.begin(9600);
  module = new YK04_Module(A_PIN, B_PIN, C_PIN, D_PIN);
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(NEAR_PIN, INPUT);
 
}


void motorAStop() {
  delay(750);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void motorAForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, maxSpeedA); 
  motorAStop();
}

void motorBStop() {
  delay(750);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void motorABackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, maxSpeedA);
  motorAStop();   
}

void motorBForward() {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, maxSpeedB); 
  motorBStop();
}

void motorBBackward() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, maxSpeedB); 
  motorBStop();
}

 
void loop() {
  Serial.print("YK04: A - " + String(module->isA()));
  Serial.print(" | B - " + String(module->isB()));
  Serial.print(" | C - " + String(module->isC()));
  Serial.println(" | D - " + String(module->isD()));
  int near = digitalRead(NEAR_PIN);
  if (near == HIGH) {
    if (module->isA()==LOW) {
      motorAForward();
    } else if (module->isB()==LOW) {
      motorABackward();
    } else if (module->isC()==LOW) {
      motorBForward();
    } else if (module->isD()==LOW) {
      motorBBackward(); 
    }
  }
 
}
