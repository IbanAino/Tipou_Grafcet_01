

#include <arduino.h>
#include "StatesFunctions.h"

// Libraries for the screen
#include "SSD1306.h"
#include "eyesPictures.h"

enum {sleep, awaike, drink};

void PerformState(bool state[3],bool *flagStateOnInit, bool *flagStateOnExit, bool *launchTempo, bool *setTempoDuration){

//------------------------------------------------------------  
  if(state[sleep]){
    Serial.println("   -> Sleep");
    // ON INIT
    if(*flagStateOnInit == true){
      *flagStateOnInit = false;
      Serial.println("   ** DO ONCE init");
      
      clearDisplay();
      drawBitmap(0, 0, sleepingEyes, 128, 46);
      screenDisplay();
    }
    // ON EXIT
    else if(*flagStateOnExit == true){
      *flagStateOnExit = false;
      Serial.println("   ## DO ONCE exit");
    }
  }

//------------------------------------------------------------
  if(state[awaike]){
    Serial.println("   -> Awaike");
    // ON INIT
    if(*flagStateOnInit == true){
      *flagStateOnInit = false;
      Serial.println("   ** DO ONCE init");
      
      clearDisplay();
      drawBitmap(0, 0, eyesAwaike, 128, 50);
      screenDisplay();

      // Tempo initialisation
      *setTempoDuration = true;
      *launchTempo = true;
    }
    // ON EXIT
    else if(*flagStateOnExit == true){
      *flagStateOnExit = false;
      Serial.println("   ## DO ONCE exit");

    }
  }
  
//------------------------------------------------------------
  if(state[drink]){
    Serial.println("   -> Drink");
    // ON INIT
    if(*flagStateOnInit == true){
      *flagStateOnInit = false;
      Serial.println("   ** DO ONCE init");
      
      clearDisplay();
      drawBitmap(25, 0, eyesDrink, 80, 64);
      screenDisplay();    
    }
    // ON EXIT
    else if(*flagStateOnExit == true){
      *flagStateOnExit = false;
      Serial.println("   ## DO ONCE exit");
      
      clearDisplay();
      drawBitmap(35, 0, eyesHappy, 62, 60);
      screenDisplay();
      delay(500);
    }
  }

}
