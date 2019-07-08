#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//enable if testing LED
#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//  #include <avr/power.h>
//#endif

#define ESP8266_BAUD 115200

#define PIN 9
#define NUM_LEDS 1
////#define BRIGHTNESS 1
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);


#define A_PIN  14
#define B_PIN  10
#define C_PIN  15
#define D_PIN  16  
#define NEAR_PIN 2

String authStr = "";
String ssidStr = "";
String passStr = "";    // Set password to "" for open networks.

int TT=3000;
int latch=1000;

int debounceT=70;

int timeout=1000;
int timeoutA=timeout;
int timeoutB=timeout;
int timeoutC=timeout;
int timeoutD=timeout;

bool tA=0;
bool tB=0;
bool tC=0;
bool tD=0;

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
//int sensorB1 = A0;
//int sensorB2 = A1;
//int sensorA1 = A2;
//int sensorA2 = A3;
int delayB = 750;

// State
bool butA = LOW;
bool butB = LOW;
bool butC = LOW;
bool butD = LOW;
bool doorClosed = false;
int doorSensor = 0;
int stateB = 2;

BLYNK_WRITE(V1) {
  int pinValue = param.asInt();
}
BLYNK_WRITE(V2) {
  int pinValue = param.asInt();
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

//  pinMode(A_PIN, INPUT);
//  pinMode(B_PIN, INPUT);    
//  pinMode(C_PIN, INPUT);
//  pinMode(D_PIN, INPUT);
  
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
  int authLen = authStr.length() + 1 ;
  int ssidLen = ssidStr.length() ;
  int passLen = passStr.length() ;
  char auth[authLen];
  char ssid[ssidLen];
  char pass[passLen];
  authStr.toCharArray(auth, authLen, 0);   
  ssidStr.toCharArray(ssid, ssidLen, 0);
  passStr.toCharArray(pass, passLen, 0);
  Blynk.begin(auth, ssid, pass);
//  Serial.print("Auth : " );
//  Serial.print(auth) ;
//  Serial.println("___");
//  Serial.print("Ssid : ");
//  Serial.print(ssid) ;
//  Serial.println("___");
//  Serial.print("Password : ");
//  Serial.print(pass) ;
//  Serial.println("___");
//  Serial.println("") ;
  
  


  //LED
//  strip.begin();
//  strip.show(); // Initialize all pixels to 'off'
//
//  lightOn(0, 255, 0);
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
  Blynk.run(); 
    
 // lightOn(0, 0, 255);
 //possibleDigitalOnlyTest();
    
  
  if (Blynk.connected()) {
    // TODO : Program indication LED as connected
  } else {
    // TODO : Program indication LED as not connected
  }


}





//LED functions
  void toggleNearLed() {
    if (digitalRead(NEAR_PIN) == HIGH) {
    } else {    
    }
  }

  void lightOn(uint8_t r, uint8_t g, uint8_t b) {
    uint16_t i;
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, r, g, b);
      strip.show();
    }
  }

//  void rainbow(uint8_t wait) {
//  uint16_t i, j;
//
//  for(j=0; j<256; j++) {
//    for(i=0; i<strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel((i+j) & 255));
//    }
//    strip.show();
//    delay(wait);
//  }
//}
//
//// Slightly different, this makes the rainbow equally distributed throughout
//void rainbowCycle(uint8_t wait) {
//  uint16_t i, j;
//
//  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
//    for(i=0; i< strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
//    }
//    strip.show();
//    delay(wait);
//  }
//}
//
// 
//
////Theatre-style crawling lights with rainbow effect
//void theaterChaseRainbow(uint8_t wait) {
//  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
//    for (int q=0; q < 3; q++) {
//      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
//        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
//      }
//      strip.show();
//
//      delay(wait);
//
//      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
//        strip.setPixelColor(i+q, 0);        //turn every third pixel off
//      }
//    }
//  }
//}
//
//
//// Input a value 0 to 255 to get a color value.
//// The colours are a transition r - g - b - back to r.
//uint32_t Wheel(byte WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if(WheelPos < 85) {
//    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  }
//  if(WheelPos < 170) {
//    WheelPos -= 85;
//    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//  WheelPos -= 170;
//  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//}
