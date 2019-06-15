#include <YK04_Module.h>

#define A_PIN  14
#define B_PIN  10
#define C_PIN  15
#define D_PIN  16  
#define NEAR_PIN 2

YK04_Module* module;
// Motor A
int enA = 6; //previously 9
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

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(NEAR_PIN, INPUT);
 
}



// Motor B is lock
int getLastBState() {
  return stateB;
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
  debugDonglePrintout();
  
  
  //temporary disable the near detection for testing
  //if ( digitalRead(NEAR_PIN) == HIGH ) {
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
