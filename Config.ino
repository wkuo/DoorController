#include <SPI.h>
#include <SD.h>

File cfgFile;

void readConfig() {
  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
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
          value.toCharArray(ssid, len, 0);
          //ssidStr = value;
        } else if (key.equalsIgnoreCase("pass")) {
          //passStr = value;
          value.toCharArray(pass, len, 0);
        } else if (key.equalsIgnoreCase("auth")) {
          value.toCharArray(auth, len+1, 0);   
          //authStr = value;
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

void printConfig() {
  Serial.print("Auth : '" );
  Serial.print(auth) ;
  Serial.println("'");
  Serial.print("Ssid : '");
  Serial.print(ssid) ;
  Serial.println("'");
  Serial.print("Password : '");
  Serial.print(pass) ;
  Serial.println("'");
  Serial.println("") ; 
}
