

#include <arduino.h>
#include "StatesFunctions.h"

// Libraries for the screen
#include "SSD1306.h"
#include "eyesPictures.h"

// File to store the notes frequencies
#include "pitches.h"

// Hardware pin out
const byte buzzer = 9;

enum {sleep, awaike, drink};

// Sounds
unsigned int soundSetup [8][2] = {
  {8,0}, // the first row contains the array size
  {NOTE_C4, 20},
  {NOTE_G3, 20},
  {NOTE_G3, 20},
  {NOTE_A3, 20},
  {NOTE_G3, 20},
  {NOTE_B3, 20},
  {NOTE_C4, 20}
};

unsigned int soundAwaike [4][2] = {
  {4,0}, // the first row contains the array size
  {NOTE_A4, 12},
  {NOTE_B4, 12},
  {NOTE_D5, 12}
};

unsigned int soundDrink [3][2] = {
  {3, 0}, // the first row contains the array size
  {NOTE_D5, 12},
  {0, 12}
};

unsigned int soundEndDrink [3][2] = {
  {3, 0}, // the first row contains the array size
  {NOTE_B5, 12},
  {0, 12}
};

//----------------------------------------
//------------ Local functions -----------
//----------------------------------------

void PlaySound(unsigned int sound[][2]){
  for (int i = 1; i < sound[i][0]; i++) {
    if(sound[i][0] == 0){
      noTone(buzzer);
      delay(sound[i][1] * 10);
    }else{
      tone(buzzer, sound[i][0]);
      delay(sound[i][1] * 10);
      noTone(buzzer);
    }
  }
}

//-------------------------------------------  
//--------------- Main function -------------
//-------------------------------------------

void PerformState(bool state[3],bool *flagStateOnInit, bool *flagStateOnExit, bool *launchTempo, bool *setTempoDuration){

//------------------------------------------------------------  
  if(state[sleep]){
    // ON INIT
    if(*flagStateOnInit == true){
      *flagStateOnInit = false;

      // Screen
      clearDisplay();
      drawBitmap(0, 0, sleepingEyes, 128, 46);
      screenDisplay();
    }
    // ON EXIT
    else if(*flagStateOnExit == true){
      *flagStateOnExit = false;
    }
  }

//------------------------------------------------------------
  if(state[awaike]){
    // ON INIT
    if(*flagStateOnInit == true){
      *flagStateOnInit = false;

       // Screen
      clearDisplay();
      drawBitmap(0, 0, eyesAwaike, 128, 50);
      screenDisplay();

      // Sound
      PlaySound(soundAwaike);

      // Tempo initialisation
      *setTempoDuration = true;
      *launchTempo = true;
    }
    // ON EXIT
    else if(*flagStateOnExit == true){
      *flagStateOnExit = false;
    }
  }
  
//------------------------------------------------------------
  if(state[drink]){
    // ON INIT
    if(*flagStateOnInit == true){
      *flagStateOnInit = false;
      
      // Screen
      clearDisplay();
      drawBitmap(25, 0, eyesDrink, 80, 64);
      screenDisplay();
    }
    // ON EXIT
    else if(*flagStateOnExit == true){
      *flagStateOnExit = false;

      // Screen
      clearDisplay();
      drawBitmap(35, 0, eyesHappy, 62, 60);
      screenDisplay();

      // Sound
      PlaySound(soundEndDrink);
      delay(500);
    }
    // MAIN ACTIONS
    else{
      // Sound
      PlaySound(soundDrink);
    }
  }

}
