#include <SPI.h>
#include <SD.h>

#define PIN_SD_CS 15

File cfgFile;

void readConfig() {
  Serial.print("Initializing SD card...");
  if (!SD.begin(PIN_SD_CS)) {
    Serial.println("Initialization failed!");
    while (1);
  }
  Serial.println("Initialization done.");
  Serial.print("Opening configuration file...");
  cfgFile = SD.open("config.txt");
  if (cfgFile) {
    Serial.println("Reading config.txt");
    bool isKey = true;
    String key = "" ;
    String value = "" ;
    while (cfgFile.available()) {
      byte b = cfgFile.read();
      if (b == 10) {
        //Serial.println("Line : " + key + " value " + value);
        int len = value.length();
        if (key.equalsIgnoreCase("ssid")) {
          ssidStr = value;
        } else if (key.equalsIgnoreCase("pass")) {
          passStr = value;
        } else if (key.equalsIgnoreCase("auth")) {
          authStr = value;
        }
        isKey = true;
        key = "";
        value ="";
      } else if (b == 61) {
        isKey = false;
      } else {
        if (isKey) {
          key =  key + char(b);
        } else {
          value = value + char(b);
        }             
      }
    }    
    cfgFile.close();
  } else {
    Serial.println("Error opening config.txt");
  }
}
