#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define ESP8266_BAUD 115200

#define UNDEFINE_0 16       // D0
#define SENSOR_LG_HALL 5    // D1
#define SENSOR_LG_CURR 4    // D2
#define SENSOR_UG_HALL 0    // D3
#define UNDEFINE_1 2        // D4
// SD_SCK 14                // D5 (SD Library pre-defined)
// SD_MISO 12               // D6 (SD Library pre-defined)
// SD_MOSI 13               // D7 (SD Library pre-defined)
#define SD_CS 15            // D8
#define SR_LOAD 10          // D9 .CS SR
#define SR_DATA 13          // D10 SER
#define SR_CLK 14           // SD3 CLOCK
#define UNDEFINE_2 9        // SD2

char auth[64];
char ssid[64];
char pass[64];  // Set password to "" for open networks.

SimpleTimer armMoveT ;
SimpleTimer buttonT ;
long armDura = 2500;
long butDura = 4500;
String armState = "IdleAtTop";
String intent = "close";
int armMoveTId = 0 ;
int buttonTId = 1 ;
unsigned long startT = 0 ;
unsigned long accumIdleT = 0 ;

boolean isArm(String txtState) {
  return armState.equalsIgnoreCase(txtState);
}

boolean isIntent(String txtState) {
  return intent.equalsIgnoreCase(txtState);  
}

void reachBottom() {
  armState = "IdleAtBottom";
  Serial.println("Arm timeout - reach bottom");
  armStop();
  if ( isIntent("open") ) {
    motorAForward(255) ;
  } 
  if ( isIntent("close") ) {
    motorABackward(255);    
  }
}

void reachTop() {
  armState = "IdleAtTop";
  Serial.println("Auto retract done");
  armStop();
  accumIdleT = 0;
}

void resetArmTop() {
  if ( isIntent("close") ) {
    motorAStop();
  }
  if ( isArm("IdleAtBottom") ) {
    Serial.println("Auto retract full");
    armUp();
    armMoveT.setTimeout(armDura, reachTop);
  }
  if ( isArm("IdleMoveDown") ) {
    Serial.print("Auto retract Partial");
    Serial.println(accumIdleT);
    armUp();
    armMoveT.setTimeout(accumIdleT, reachTop);
  }
}

BLYNK_WRITE(V1) {
  // OpenDoor 
  // One press -> Press (armDown, reachBottom, open) Release (Idle -> timeout, armUp, idle)
  // Multi -> Press (armDown) Release (idle) Press (armDown, reachBottom, open) Release (idle) Press (open) Release (idle, timeout, armUp, idle)
  // Incomplete -> Press (armDown, until any half way) Release (Idle, timeout, armUp, idle)
  int pinValue = param.asInt();
  intent = "open";
  if (pinValue > LOW) {
    if ( isArm("IdleAtTop") || isArm("MoveDown") || isArm("IdleMoveDown") ) {
      armDown();
      if ( isArm("IdleMoveDown") ) {
        startT = millis(); 
        armMoveT.enable(armMoveTId);   
        armState = "MoveDown"; 
      }
      if ( isArm("IdleAtTop") ) {
        startT = millis();
        armMoveTId = armMoveT.setTimeout(armDura, reachBottom);
        armState = "MoveDown";
      }
    } 
    if ( isArm("IdleAtBottom") ) {
      motorAForward(255); 
    }
  } else {
     if ( isArm("MoveDown") ) {
        accumIdleT = millis() - startT + accumIdleT ;
        armMoveT.disable(armMoveTId);
        armState = "IdleMoveDown";
     }
     if ( (isArm("IdleMoveDown") || isArm("IdleAtBottom")) ) {
       buttonT.deleteTimer(buttonTId);
       buttonTId = buttonT.setTimeout(butDura, resetArmTop);
     }
     armStop();
     motorAStop();
  }
}

BLYNK_WRITE(V2) {
  // CloseDoor Trigger -> Check timeout -> rigDown -> closeDirection -> release ->  check another timeout -> stop push -> rigUp.
  int pinValue = param.asInt();
  intent = "close";
  if (pinValue > LOW) {
   if ( isArm("IdleAtTop") || isArm("MoveDown") || isArm("IdleMoveDown") ) {
      armDown();
      if ( isArm("IdleMoveDown") ) {
        startT = millis(); 
        armMoveT.enable(armMoveTId);   
        armState = "MoveDown"; 
      }
      if ( isArm("IdleAtTop") ) {
        startT = millis();
        armMoveTId = armMoveT.setTimeout(armDura, reachBottom);
        armState = "MoveDown";
      }
    } 
    if ( isArm("IdleAtBottom") ) {
        motorABackward(255); 
    }
  } else {
     if ( isArm("MoveDown") ) {
        accumIdleT = millis() - startT + accumIdleT ;
        armMoveT.disable(armMoveTId);
        armState = "IdleMoveDown";
     }
     if ( (isArm("IdleMoveDown") || isArm("IdleAtBottom")) ) {
       buttonT.deleteTimer(buttonTId);
       buttonTId = buttonT.setTimeout(butDura, resetArmTop);
     }
     armStop();
     motorAStop();
  }
}
BLYNK_WRITE(V3) {
  int pinValue = param.asInt();
 if (pinValue > LOW) {  
  Serial.println("reset");
  Serial.print(accumIdleT);
  accumIdleT=0;
  armState = "IdleAtTop";
  armMoveT.restartTimer(armMoveTId);
  buttonT.restartTimer(buttonTId);
  }
}
BLYNK_WRITE(V4) {
  int pinValue = param.asInt();
}

void setup() { 
  Serial.begin(ESP8266_BAUD);
  // Set all the motor control pins to outputs

  //motor initialization
//  pinMode(in1, OUTPUT);
//  pinMode(in2, OUTPUT);
//  pinMode(in3, OUTPUT);
//  pinMode(in4, OUTPUT);
//  motorAStop();
//  motorBStop();

  //ESP connection
//  pinMode(NEAR_PIN, INPUT);

  readConfig();
  printConfig(); 
  Blynk.begin(auth, ssid, pass);

  // Set pin mode
  pinMode(SR_CLK, OUTPUT);
  pinMode(SR_LOAD, OUTPUT);
  pinMode(SR_DATA, OUTPUT);

  //LED
//  strip.begin();
//  strip.show(); // Initialize all pixels to 'off'
//
//  lightOn(0, 255, 0);
}

 
void loop() {
  armMoveT.run();
  buttonT.run();
  Blynk.run(); 
  // TODO : Program indication LED as device turned on
  // lightOn(0, 0, 255);

  if (Blynk.connected()) {
    // TODO : Program indication LED as connected (ready)
  } else {
    // TODO : Program indication LED as not connected
  }
}
