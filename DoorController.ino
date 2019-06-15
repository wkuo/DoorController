#include <YK04_Module.h>
//https://github.com/YuriiSalimov/YK04_Module/blob/master/src/YK04_Module.cpp
//https://github.com/YuriiSalimov/YK04_Module/blob/master/src/YK04_Module.h

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

void doorClose(int motorspeed) {
  motorAForward(motorspeed);
}
void doorOpen(int motorspeed) {
  motorABackward(motorspeed);
}
void lock(int motorspeed) {
  motorBForward(motorspeed);
}
void unlock(int motorspeed) {
  motorBBackward(motorspeed);
}


 
void loop() {
  debugDonglePrintout();
  
  
  //temporary disable the near detection for testing
  //if ( digitalRead(NEAR_PIN) == HIGH ) {
    if (module->isA()==LOW) {
      while(module->isA()==LOW)
        motorAForward(255);
    } else if (module->isB()==LOW) {
      while (module->isB()==LOW)
        motorABackward(255);
    } else if (module->isC()==LOW) {
      while (module->isC()==LOW)
        motorBForward(255);
    } else if (module->isD()==LOW) {
      while (module->isD()==LOW)
        motorBBackward(255); 
    }
    else{
      motorAStop();
      motorBStop();
    }

  // possibleDigitalOnlyTest();// to test if YK04 is only digital read
 
}





void possibleDigitalOnlyTest(){
    pinMode(A_PIN, INPUT);
    pinMode(B_PIN, INPUT);    
    pinMode(C_PIN, INPUT);
    pinMode(D_PIN, INPUT);
    digitalWrite(A_PIN, HIGH);
    digitalWrite(B_PIN, HIGH);
    digitalWrite(C_PIN, HIGH);
    digitalWrite(D_PIN, HIGH);

        
    if (digitalRead(A_PIN)==LOW) {
      while(module->isA()==LOW)
        motorAForward(255);
    }
    
    else if (digitalRead(B_PIN)==LOW) {
      while (module->isB()==LOW)
        motorABackward(255);
    }
    
    else if (digitalRead(C_PIN)==LOW) {
      while (module->isC()==LOW)
        motorBForward(255);
    } 
    
    else if (digitalRead(D_PIN)==LOW) {
      while (module->isD()==LOW)
        motorBBackward(255); 
    }
    
    else{
      
      motorAStop();
      motorBStop();
      
    }

    
}


