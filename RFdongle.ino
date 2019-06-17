  void fastandfurious(){
    
        
      if( digitalRead(A_PIN)==HIGH ){
      
        motorAForward(255);
        lightOn(255, 0, 0);
        delay(TT);
        motorAStop();
        lightOn(0, 255, 0);
      }
      if( digitalRead(B_PIN)==HIGH ){
      
        motorABackward(255);
        lightOn(255, 0, 0);
        delay(TT);
        motorAStop();
        lightOn(0, 255, 0);
      }
  
      if( digitalRead(C_PIN)==HIGH ){
      
        motorBForward(255);
        lightOn(0, 0, 255);//RGB
        delay(latch);
        motorBStop();
        lightOn(0, 255, 0);
      }
      if( digitalRead(D_PIN)==HIGH ){
      
        motorBBackward(255);
        lightOn(0, 0, 255);
        delay(latch);
        motorBStop();
        lightOn(0, 255, 0);
      } 
  }  



  void possibleDigitalOnlyTest(){




    int tempA = digitalRead(A_PIN);
    int tempB = digitalRead(B_PIN);
    int tempC = digitalRead(C_PIN);
    int tempD = digitalRead(D_PIN);

    
    if (digitalRead(A_PIN)==HIGH) {
      butA = HIGH;
      timeoutA=timeout;
      Serial.println("A on");
   
    } else  {
      if (butA==HIGH) {
        timeoutA=timeoutA-1;
        Serial.print(butA);Serial.print(" , ");Serial.println(timeoutA);
        
        }
      }
     
    
    if(timeoutA<=0){
      butA = LOW;
      Serial.print(butA);Serial.print(" , ");Serial.println("A off");
      timeoutA=timeout;
    }




    
    if (tempB==HIGH) {
      butB = HIGH;
      Serial.println("B on");
    
    } else if (tempB==LOW) {
      if (butB==HIGH) {
        delay(debounceT);
        if (digitalRead(B_PIN)==LOW) {
          butB = LOW;
          Serial.println("B off");
          
        }
      }
    }
    if (tempC==HIGH) {
      butC = HIGH;
      Serial.println("C on");
    } else if (tempC==LOW) {
      if (butC==HIGH) {
        delay(debounceT);
        if (digitalRead(C_PIN)==LOW) {
          butC = LOW;
          Serial.println("C off");
        }
      }
    }
    if (tempD==HIGH) {
      butD = HIGH;
      Serial.println("D on");
    } else if (tempD==LOW) {
      if (butD==HIGH) {
        delay(debounceT);
        if (digitalRead(D_PIN)==LOW) {
          butD = LOW;
          Serial.println("D off");
        }
      }
    }    
//    if (digitalRead(B_PIN)==HIGH) {
//        butB = HIGH;
//    }
//    if (digitalRead(B_PIN)==LOW) {
//      delay(50);
//      if (digitalRead(B_PIN)==LOW) {
//        butB = LOW;
//      }
//    }


    // Door    
    if (butA==HIGH) {
      motorAForward(255);
      //lightOn(0, 255, 255);
    } else if (butB==HIGH) {
      motorABackward(255);
      //lightOn(0, 255, 255);
      //Serial.println("A backward " + digitalRead(B_PIN));
    } else {
      motorAStop();
    }
    
    // Lock
    if (butC==HIGH) {
        motorBForward(255);
        lightOn(0, 255, 255);
        //Serial.println("B foreward " + digitalRead(C_PIN));
    } 
    else if (butD==HIGH) {
        motorBBackward(255);
          lightOn(0, 255, 255);
        //Serial.println("B Backward" + digitalRead(D_PIN));
    } else {
      motorBStop();
    }

//    if (butA==LOW && butB==LOW && butC==LOW && butD==LOW) {
//     if (lighting)       lightOn(255, 0, 0);
//    }
    
}
