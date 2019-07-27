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

#define A_PIN  14
#define B_PIN  10
#define C_PIN  15
#define D_PIN  16  
#define NEAR_PIN 2

char auth[64];
char ssid[64];
char pass[64];  // Set password to "" for open networks.
//String authStr = "";
//String ssidStr = "";
//String passStr = "";    

// B0000 0000 // all off
// B0000 0001 // Door opening 
// B0000 0010 // Door closing
// B0000 0100 // Touch down
// B0000 1000 // Jack Up
// B0001 0000 // Door unlocking
// B0010 0000 // Door locking

#define ST_IDLE B00000000
#define ST_OPEN B00000001
#define ST_CLOSE 2
#define ST_UNLOCK 16
#define ST_LOCK 32


int TT=3000;
int latch=1000;

int debounceT=70;

int timeout=1000;
int timeoutA=1000;

// Motor A
int enA = 6; //previously 9
int in1 = 8;
int in2 = 7;
 
// Motor B 
int enB = 3;
int in3 = 5;
int in4 = 4;

// State
bool butA = LOW;
bool butB = LOW;
bool butC = LOW;
bool butD = LOW;

bool doorClosed = true;
bool armUp = true;
int intent = 0;

BLYNK_WRITE(V1) {
  // Open Door
  int pinValue = param.asInt();
  Serial.print(pinValue);
  if (pinValue > LOW) {
    intent = ST_OPEN;
  }
  if (intent == ST_OPEN) {
    writeSR(4);
    delay(1000);
    writeSR(ST_OPEN);
    delay(5000);
    writeSR(8);
    intent = 0;
  } else {
    writeSR(ST_IDLE);
  }
  
}
BLYNK_WRITE(V2) {
  int pinValue = param.asInt();
  if (pinValue > LOW) {
    intent = ST_CLOSE;
  }
  if (intent == ST_CLOSE) {
    writeSR(4);
    delay(1000);
    writeSR(ST_OPEN);
    delay(5000);
    writeSR(8);
    intent = 0;
  } else {
    writeSR(ST_IDLE);
  }
}
BLYNK_WRITE(V3) {
  int pinValue = param.asInt();
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
//  int authLen = authStr.length() + 1 ;
//  int ssidLen = ssidStr.length() ;
//  int passLen = passStr.length() ;
//  char authL[authLen];
//  char ssidL[ssidLen];
//  char passL[passLen];
  //authStr.toCharArray(auth, authLen, 0);   
  //ssidStr.toCharArray(ssid, ssidLen, 0);
  //passStr.toCharArray(pass, passLen, 0);
//  auth = authL;
//  ssid = ssidL;
//  pass = passL;
//  strcpy(auth, authStr.c_str());
//  strcpy(ssid, ssidStr.c_str());
//  strcpy(pass, passStr.c_str());
  printConfig(); 
  Blynk.begin(auth, ssid, pass);

  // Set pin mode
  pinMode(SR_CLK, OUTPUT);
  pinMode(SR_LOAD, OUTPUT);
  pinMode(SR_DATA, OUTPUT);
  writeSR(ST_IDLE);

  //LED
//  strip.begin();
//  strip.show(); // Initialize all pixels to 'off'
//
//  lightOn(0, 255, 0);
}



//void doorClose(int motorspeed) {
//  motorAForward(motorspeed);
//}
//void doorOpen(int motorspeed) {
//  motorABackward(motorspeed);
//}
//void lock(int motorspeed) {
//  motorBForward(motorspeed);
//}
//void unlock(int motorspeed) {
//  motorBBackward(motorspeed);
//}

 
void loop() {
  Blynk.run(); 
 // lightOn(0, 0, 255);

  if (Blynk.connected()) {
      //testShiftReg();
    // TODO : Program indication LED as connected
  } else {
    // TODO : Program indication LED as not connected
  }
}
