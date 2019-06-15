#include <YK04_Module.h>

#define A_PIN  14
#define B_PIN  10
#define C_PIN  15
#define D_PIN  16  
#define NEAR_PIN 2

YK04_Module* module;
// Motor A
//int enA = 9;
int enA = 6;
int in1 = 8;
int in2 = 7;
int maxSpeedA = 255;
int delayA = 10000;
int stateA = 0;
 
// Motor B 
int enB = 3;
int in3 = 5;
int in4 = 4;
int sensorB1 = A0;
int sensorB2 = A1;
int sensorA1 = A2;
int sensorA2 = A3;
int maxSpeedB = 255;
int delayB = 750;
int stateB = 0;


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

// Motor A is door
void motorAStop() {
  delay(delayA);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void motorAForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //analogWrite(enA, maxSpeedA); 
  motorAStop();
}

void motorABackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, maxSpeedA);
  motorAStop();   
}


// Motor B is lock
int getLastBState() {
  return stateB;
}

void motorBStop() {
  delay(delayB);
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
  
  motorBStop();
}

void motorBBackward() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, maxSpeedB); 
  motorBStop();
}

void doorClose() {
  motorAForward();
}
void doorOpen() {
  motorABackward();
}
void lock() {
  motorBForward();
}
void unlock() {
  motorBBackward();
}
 
void loop() {
  Serial.print("YK04: A - " + String(module->isA()));
  Serial.print(" | B - " + String(module->isB()));
  Serial.print(" | C - " + String(module->isC()));
  Serial.println(" | D - " + String(module->isD()));
  int near = digitalRead(NEAR_PIN);
  //temporary disable the near detection for testing
  //if (near == HIGH) {
    if (module->isA()==LOW) {
      motorAForward();
    } else if (module->isB()==LOW) {
      motorABackward();
    } else if (module->isC()==LOW) {
      motorBForward();
    } else if (module->isD()==LOW) {
      motorBBackward(); 
    }
  //}
 
}
