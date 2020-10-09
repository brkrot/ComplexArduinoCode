
#include "Arduino.h"
#include "led.h"

#define LEDPIN 13
const int ledPin = 13;
//Ctor
led::led(){
}
//setup function
void led::SETUP(){
    pinMode(LEDPIN, OUTPUT);
    digitalWrite(LEDPIN, HIGH);
}

//Blinking the led |times| times
void led::blink(int times){
  for(int i=0;i<times;i++){
    digitalWrite(LEDPIN,HIGH);
    delay(250);
    digitalWrite(LEDPIN,LOW);
    delay(250);
  }
}

led l = led();
