#include "StatesFunctions.h"

// Hardware input pins
const byte button1 = 8;
const byte button2 = 9;
const byte button3 = 10;

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

// Flag to perform a loop only once at the launch of each state
bool flagInitState = true;

//************************* FUNCTIONS ****************************

void ReadInputs(){
  shake = digitalRead(button1) == LOW ? true : false;
  water = digitalRead(button2 )== LOW ? true : false;
  noWater  = digitalRead(button2) == LOW ? false : true;
  lightOff = digitalRead(button3) == LOW ? true : false;
}

void ComputeTransitions(){
  transition[0] = state[sleep] && shake;
  transition[1] = state[awaike] && water;
  transition[2] = state[awaike] && lightOff;
  transition[3] = state[drink] && noWater;
}

void DesactivateStates(){
  if(transition[0]) state[sleep] = false;
  if(transition[1]) state[awaike] = false;
  if(transition[2]) state[awaike] = false;
  if(transition[3]) state[drink] = false;
}

void ActivateStates(){
  if(transition[0]){
    state[awaike] = true;
    flagInitState = true;
  }
  if(transition[1]){
    state[drink] = true;
    flagInitState = true;
  }
  if(transition[2]){
    state[sleep] = true;
    flagInitState = true;
  }
  if(transition[3]){
    state[awaike] = true;
    flagInitState = true;
  }
}

//**************************** SETUP *****************************

void setup() {
  // Init hardware Input and Outputs
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  // Setup communication with the PC
  Serial.begin(9600);
  Serial.println("Program initialisation");

  // Set setps to 0, exept the forst step that is set to 1.
  for(int i = 0; i < 2; i++){
    state[i] = false;
  }
  state[sleep] = true;
}

//********************************* MAIN LOOP ************************

void loop() {

  ReadInputs();
  ComputeTransitions();
  DesactivateStates();
  ActivateStates();
  PerformState(state, &flagInitState);

  // Debug messages to monitor the grafcet avancment
  Serial.println("Input states :");
  Serial.print("   shake    => ");
  Serial.println(shake);
    //Serial.println(digitalRead(button1));
  Serial.print("   water    => ");
  Serial.println(water);
    //Serial.println(digitalRead(button2));
  Serial.print("   noWater  => ");
  Serial.println(noWater);
    //Serial.println(!digitalRead(button2));
  Serial.print("   lightOff => ");
  Serial.println(lightOff);
    //Serial.println(digitalRead(button3));

  for(int i = 0; i < 4; i++){
    Serial.print("Transition ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(transition[i]);
  }

  for(int i = 0; i < 3; i++){
    Serial.print("State ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(state[i]);
  }

  Serial.println("---------------------");
  delay(1000);
}
