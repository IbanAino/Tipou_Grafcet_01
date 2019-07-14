
#include <arduino.h>
#include "StatesFunctions.h"

// Libraries for the screen
#include "SSD1306.h"
#include "eyesPictures.h"

enum {sleep, awaike, drink};

void PerformState(bool state[3],bool *flagInitState){
   
  if(state[sleep]){
    Serial.println("-> Sleep");

    if(*flagInitState == true){
      *flagInitState = false;
      Serial.println("DO ONCE");
      
      clearDisplay();
      drawBitmap(0, 0, sleepingEyes, 128, 46);
      screenDisplay();
    }
  }
  
  if(state[awaike]){
    Serial.println("-> Awaike");
    
    if(*flagInitState == true){
      *flagInitState = false;
      Serial.println("DO ONCE");
      
      clearDisplay();
      drawBitmap(0, 0, eyesAwaike, 64, 48);
      screenDisplay();   
    } 
  }
  
  if(state[drink]){
    Serial.println("-> Drink");
    
    if(*flagInitState == true){
      *flagInitState = false;
      Serial.println("DO ONCE");
      
      clearDisplay();
      drawBitmap(0, 0, eyesTears, 128, 64);
      screenDisplay();    
    }
  }

}
