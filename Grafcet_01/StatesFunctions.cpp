
#include <arduino.h>
#include "StatesFunctions.h"

enum {sleep, awaike, drink};

void PerformState(bool state[3],bool *flagInitState){
   
  if(state[sleep]){
    Serial.println("-> Sleep");

    if(*flagInitState == true){
      *flagInitState = false;
      Serial.println("DO ONCE");     
    }
  }
  
  if(state[awaike]){
    Serial.println("-> Awaike");
    
    if(*flagInitState == true){
      *flagInitState = false;
      Serial.println("DO ONCE");     
    } 
  }
  
  if(state[drink]){
    Serial.println("-> Drink");
    
    if(*flagInitState == true){
      *flagInitState = false;
      Serial.println("DO ONCE");     
    }
  }

}
