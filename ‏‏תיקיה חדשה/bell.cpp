
#include "Arduino.h"
#include "bell.h"

#define BELLPIN 7

//Ctor
bell::bell(){
}
//setup function
void bell::SETUP(){
    pinMode(BELLPIN, OUTPUT);
    digitalWrite(BELLPIN, LOW);
}

//Make A SOUND FROM THE BEEPER |times| times
void bell::buzz(int times){
  for(int i=0;i<times;i++){
    digitalWrite(BELLPIN,HIGH);
    delay(250);
    digitalWrite(BELLPIN,LOW);
    delay(250);
  }
}

bell b = bell();
