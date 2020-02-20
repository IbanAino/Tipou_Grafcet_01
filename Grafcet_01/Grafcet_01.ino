#define DEBUG(false)

#include "StatesFunctions.h"

// Hardware input pins
const byte button1 = 5; // shake sensor
const byte button2 = 2; // water sensor
const byte button3 = 3; // light sensor


// States of the grafcet, indended with its enum to be easy to understand inside the source code
bool state[3];
enum {sleep, awaike, drink};

// Grafcet transitions table
bool transition[4];

// Inputs from sensors for transitions formulas
bool shake = false;
bool water = false;
bool noWater = true;
bool lightOff = false;

// Flag to perform a loop only once for each state execution
bool flagStateOnInit = true;
bool flagStateOnExit = false;

// Temporisation variables
//unsigned long tempoDuration = 0;
unsigned long tempoEndTime = 0;
bool tempoOver = false;
bool launchTempo = false;
bool setTempoDuration = false;

// Light sensor variables
bool lightTempoLaunched = false;
unsigned long lightTempoDuration = 0;

//************************* FUNCTIONS ****************************

void ReadInputs(){
  shake = digitalRead(button1) == LOW ? true : false;
  water = digitalRead(button2 )== LOW ? true : false;
  noWater  = digitalRead(button2) == LOW ? false : true;
  //lightOff = digitalRead(button3) == LOW ? true : false;
}

void ComputeTransitions(){
  transition[0] = state[sleep] && shake && !lightOff;
  transition[1] = state[awaike] && water;
  transition[2] = (state[awaike] && lightOff) || (state[awaike] && tempoOver);
  transition[3] = state[drink] && noWater;
}

void ExitStates(){
  if(transition[0]) flagStateOnExit = true;
  if(transition[1]) flagStateOnExit = true;
  if(transition[2]) flagStateOnExit = true;
  if(transition[3]) flagStateOnExit = true;
}

void DesactivateStates(){
  if(transition[0]) state[sleep] = false;
  if(transition[1]) state[awaike] = false;
  if(transition[2]) state[awaike] = false;
  if(transition[3]) state[drink] = false;
}

void InitStates(){
  if(transition[0])flagStateOnInit = true;
  if(transition[1])flagStateOnInit = true;
  if(transition[2])flagStateOnInit = true;
  if(transition[3])flagStateOnInit = true;
}

void ActivateStates(){
  if(transition[0]) state[awaike] = true;
  if(transition[1]) state[drink] = true;
  if(transition[2]) state[sleep] = true;
  if(transition[3]) state[awaike] = true;
}

void ManageTempo(){
  if(launchTempo){
    if(setTempoDuration){
      setTempoDuration = false;
      tempoEndTime = 10000 + millis();
      tempoOver = false;
    }
    if(tempoEndTime < millis()){
      tempoOver = true;
      launchTempo = false;
    }
  } 
}

void ManageLightSensor(){
  // read the light sensot value
  bool lightSensor = digitalRead(button3) == LOW ? true : false;

  if(lightSensor){ // light ON
  lightOff = false;
    // Set the tempo duration
    if(lightTempoLaunched){
      lightTempoLaunched = false;
      lightTempoDuration = millis() + 1000;      
    }
  }else{ // light OFF
    if(lightTempoLaunched){
      if(lightTempoDuration < millis()){
        lightOff = true;
      }
    }else{
      lightTempoLaunched = true;
      lightTempoDuration = millis() + 1000;
    }
  } 
}

//**************************** SETUP *****************************

void setup() {
  // Init hardware Input and Outputs
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

#if DEBUG
  // Setup communication with the PC
  Serial.begin(9600);
  Serial.println("Program initialisation");
#endif

  // Set setps to 0, exept the forst step that is set to 1.
  for(int i = 0; i < 2; i++){
    state[i] = false;
  }
  state[sleep] = true;
  
  // Setup the LCD screen
  InitializeDisplay();
  clearDisplay(); 
}

//********************************* MAIN LOOP ************************

void loop() {
  
  ReadInputs();
#if DEBUG
  Serial.println("Read inputs");
  Serial.print("   shake    => ");
  Serial.println(shake);
  Serial.print("   water    => ");
  Serial.println(water);
  Serial.print("   noWater  => ");
  Serial.println(noWater);
  Serial.print("   lightOff => ");
  Serial.println(lightOff);
#endif

  ManageTempo();
#if DEBUG
  Serial.println("Manage tempo");
  Serial.print("   launchTempo : ");
  Serial.println(launchTempo);
  Serial.print("   tempoOver : ");
  Serial.println(tempoOver);
#endif

  ManageLightSensor();
#if DEBUG
  Serial.println("ManageLightSensor");
  Serial.print("   lightOff");
  Serial.println(lightOff);
#endif
 
  ComputeTransitions();
#if DEBUG
  Serial.println("Compute transitions");
  for(int i = 0; i < 4; i++){
    Serial.print("   Transition ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(transition[i]);
  }
#endif
 
  ExitStates();
#if DEBUG
  Serial.println("Exit states");
#endif
  if(flagStateOnExit){
#if DEBUG
    Serial.println("Perform states");
#endif
    PerformState(state, &flagStateOnInit, &flagStateOnExit, &launchTempo, &setTempoDuration);
  }

  DesactivateStates();
#if DEBUG
  Serial.println("Desactivate States");
#endif

  InitStates();
#if DEBUG
  Serial.println("Init states");
#endif
  ActivateStates();
#if DEBUG
  Serial.println("Activate states");
  for(int i = 0; i < 3; i++){
    Serial.print("   State ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(state[i]);
  }
#endif

  if(flagStateOnInit){
#if DEBUG
    Serial.println("Perform states");
#endif
    PerformState(state, &flagStateOnInit, &flagStateOnExit, &launchTempo, &setTempoDuration);
  }

#if DEBUG
  Serial.println("Perform states");
#endif
  PerformState(state, &flagStateOnInit, &flagStateOnExit, &launchTempo, &setTempoDuration);
/*
  Serial.println("millis() and tempoEndTime :");
  Serial.println(millis());
  Serial.println(tempoEndTime);

  Serial.println("freezeComputeTransitions :");
  Serial.println(freezeComputeTransitions);
*/
#if DEBUG
  Serial.println("---------------------");
#endif
  
  //delay(1000);
}
