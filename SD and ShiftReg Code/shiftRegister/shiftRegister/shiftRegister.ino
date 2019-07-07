
//following tutorial
//https://techtutorialsx.com/2016/08/30/esp8266-connection-to-sn74hc595/

const int dataPin = 12;   //Outputs the byte to transfer
const int loadPin = 13;   //Controls the internal transference of data in SN74HC595 internal registers
const int clockPin = 15;  //Generates the clock signal to control the transference of data

void setup() {

      pinMode(dataPin, OUTPUT);
      pinMode(loadPin, OUTPUT);
      pinMode(clockPin, OUTPUT);

}

//GPIO12 D6 to SER
//GPIO13 D7 to RCLK
//GPIO15 D8 to SRCLK

void loop() {
      
      byte data = B00000001;
      digitalWrite(loadPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, data); 
      digitalWrite(loadPin, HIGH);
      delay(500);
      
      data = B00000010;
      digitalWrite(loadPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, data); 
      digitalWrite(loadPin, HIGH);
      delay(500);
      
      data = B00000100;
      digitalWrite(loadPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, data); 
      digitalWrite(loadPin, HIGH);
      delay(500);
      
}      
