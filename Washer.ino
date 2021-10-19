//Fill in the values below with the pins that you chose to use

#include <Arduino.h>
#include <Wire.h>

const int POT_PIN = A0 ;
const int BUTTON_PIN = 2 ;

const int HOT_PIN = 4 ;
const int COLD_PIN = 9;
const int DRY_PIN = 8;
const int LOCK_PIN = 13;

enum State {        
  idle,
  ecold,        
  edry,        
  dhot,        
  ddry,        
  sdhot,
  sdmedium,        
  sddry,                
};

State counterState = idle; //What state are we currently in?


void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);      //let the button be the INPUT_PULLUP
  pinMode(POT_PIN, INPUT);                //let the pot be an INPUT
  pinMode(LOCK_PIN,OUTPUT);           //let lock_pin be the output       //turn on lock light 
  pinMode(COLD_PIN,OUTPUT);           
  pinMode(HOT_PIN,OUTPUT);
  pinMode(DRY_PIN,OUTPUT);
}

void loop() {
  counterState = determineNextState(counterState);
}

State determineNextState(State currentState)
  {

  switch (currentState)
   {
     case idle:
//        pinMode(LOCK_PIN,OUTPUT);           //let lock_pin be the output
        digitalWrite(LOCK_PIN, LOW);        //turn on lock light 
//        pinMode(COLD_PIN,OUTPUT);           
        digitalWrite(COLD_PIN,LOW);
//        pinMode(HOT_PIN,OUTPUT);
        digitalWrite(HOT_PIN,LOW);
//        pinMode(DRY_PIN,OUTPUT);
        digitalWrite(DRY_PIN,LOW);
        if(digitalRead(BUTTON_PIN) == LOW)
        {
          if(analogRead(POT_PIN) >= 1000)
          {
            pprint(currentState);
            currentState = ecold;
          }
          else if(analogRead(POT_PIN) >= 510 && analogRead(POT_PIN) <= 530)
          {
            pprint(currentState);
            currentState = dhot;
          }
          else if(analogRead(POT_PIN) <= 10)
          {
            pprint(currentState);
            currentState = sdhot;
          }
        }
        else
        {
          pprint(currentState);
          currentState = idle;
        }
        break;
   

      case ecold:
//        pinMode(LOCK_PIN,OUTPUT);
        digitalWrite(LOCK_PIN, HIGH);
//        pinMode(COLD_PIN,OUTPUT);
        digitalWrite(COLD_PIN,HIGH);
        delay(5000);
        digitalWrite(LOCK_PIN, LOW);
        digitalWrite(COLD_PIN, LOW);
      if(analogRead(POT_PIN) <= 10)           //if the pot is switched to supper deluxe
      {
        pprint(currentState);
        currentState = sddry;
      }
      else if(analogRead(POT_PIN) >= 510 && analogRead(POT_PIN) <= 530)       //if the pot is switched to deluxe
      {
        pprint(currentState);
        currentState = ddry;
      }
      else                  //proceed to economical dry state if the pot is not switched to other modes
      {
        pprint(currentState);
        currentState = edry;
      }
      break;

      case edry:
//        pinMode(LOCK_PIN,OUTPUT);
        digitalWrite(LOCK_PIN, HIGH);
//        pinMode(DRY_PIN,OUTPUT);
        digitalWrite(DRY_PIN,HIGH);
        delay(2000);
        digitalWrite(LOCK_PIN, LOW);
        digitalWrite(DRY_PIN, LOW);
        pprint(currentState);
        currentState = idle;
        break;
//   }
      
//    else if(analogRead(POT_PIN) >= 510 && analogRead(POT_PIN) <= 530)       //if the pot is in the deluxe mode
//    {
      case dhot:
//        pinMode(LOCK_PIN,OUTPUT);
        digitalWrite(LOCK_PIN, HIGH);
//        pinMode(HOT_PIN,OUTPUT);
        digitalWrite(HOT_PIN,HIGH);
        delay(7000);
        digitalWrite(LOCK_PIN, LOW);
        digitalWrite(HOT_PIN, LOW);
      if(analogRead(POT_PIN) >= 1000)           //if the pot is switched to econ mode
      {
        pprint(currentState);
        currentState = edry;
      }
      else                      //proceed to deluxe dry state because if the pot is switched to super deluxe mode, the deluxe dry state is the same as the super deluxe dry state
      {
        pprint(currentState);
        currentState = ddry;
      }
      break;

      case ddry:
//        pinMode(LOCK_PIN,OUTPUT);
        digitalWrite(LOCK_PIN, HIGH);
//        pinMode(DRY_PIN,OUTPUT);
        digitalWrite(DRY_PIN,HIGH);
        delay(7000);
        digitalWrite(LOCK_PIN, LOW);
        digitalWrite(DRY_PIN, LOW);
        pprint(currentState);
        currentState = idle;
        break;
//    } 
      
//    else if(analogRead(POT_PIN) <= 10)      //
//    {
      case sdhot:
//        pinMode(LOCK_PIN,OUTPUT);
        digitalWrite(LOCK_PIN, HIGH);
//        pinMode(HOT_PIN,OUTPUT);
        digitalWrite(HOT_PIN,HIGH);
        delay(7000);
        digitalWrite(LOCK_PIN, LOW);
        digitalWrite(HOT_PIN, LOW);
       if(analogRead(POT_PIN) >= 1000)
      {
        pprint(currentState);
        currentState = edry;
      }
      else
      {
        pprint(currentState);
        currentState = sdmedium;
      }
      break;

      case sdmedium:
//        pinMode(LOCK_PIN,OUTPUT);
        digitalWrite(LOCK_PIN, HIGH);
//        pinMode(HOT_PIN,OUTPUT);
        digitalWrite(HOT_PIN,HIGH);
//        pinMode(COLD_PIN, OUTPUT);
        digitalWrite(COLD_PIN,HIGH);
        delay(7000);
        digitalWrite(LOCK_PIN, LOW);
        digitalWrite(HOT_PIN, LOW);
        digitalWrite(COLD_PIN, LOW);
      if(analogRead(POT_PIN) >= 1000)
      {
        pprint(currentState);
        currentState = edry;
      }
      else
      {
        pprint(currentState);
        currentState = sddry;
      }
      break;

      case sddry:
//        pinMode(LOCK_PIN,OUTPUT);
        digitalWrite(LOCK_PIN, HIGH);
//        pinMode(DRY_PIN,OUTPUT);
        digitalWrite(DRY_PIN,HIGH);
        delay(7000);
        digitalWrite(LOCK_PIN, LOW);
        digitalWrite(DRY_PIN, LOW);
        pprint(currentState);
        currentState = idle;
        break;
//    }
//   }
//    else
//    {
//      pprint(currentState);
//      currentState = idle; 
   }
   return currentState;
  }

void pprint(State stateToPrint) {
  Serial.print(stateToPrint);
} 
