#include <YK04_Module.h>
//https://github.com/YuriiSalimov/YK04_Module/blob/master/src/YK04_Module.cpp
//https://github.com/YuriiSalimov/YK04_Module/blob/master/src/YK04_Module.h


//enable if testing LED
//#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//  #include <avr/power.h>
//#endif

//#define PIN 9
//#define NUM_LEDS 1
////#define BRIGHTNESS 1
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);



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

  //motor initialization
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //ESP connection
  pinMode(NEAR_PIN, INPUT);

  //LED
  //strip.begin();
  //strip.show(); // Initialize all pixels to 'off'
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


  //LED
  //rainbow(20);
  //rainbowCycle(20);
  //theaterChaseRainbow(50);
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






//LED functions
/*
 * void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

 

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

 */
