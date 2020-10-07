

/********************* Includes ***************************/
#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "Arduino.h"
#include "led.h"
#include "bell.h"
#include "screen.h"
#include "AirCondition.h"
//tru comment

/*********************Constants*********************************/

#define LCD_DELAY_TIME 5000

/*********************Ports*********************************/
#define X_PIN A0                //Naming all the used PINs
#define Y_PIN A1
#define BUZZER 7
#define IR_RECEIVE_PIN 11
#define PUSH_BUTTON 12


/****************Variables*********************************/
unsigned long lastTime = 0;
unsigned long currentTime = 0;
int xData = 0;
int yData = 0;
char currentDirection = 'N';
boolean setupMode = false;



void beep(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(50);
    digitalWrite(BUZZER, LOW);
    delay(50);
  }
}

int get_free_memory()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
//***************- Setup *********************************//
void setup() {

  //initLcd();    //Initializing the lcd screen
  beep(2);    //A beep to let the user know the system is up

  pinMode(PUSH_BUTTON, INPUT);
 Serial.begin(9600);
  //Setup all the parts of the files
  l.SETUP();    // Setup for the led
  b.SETUP();    // Setup for the bell
  Serial.print(F("Free memory "));
  Serial.println(get_free_memory(), DEC);
  
  
  s.SETUP();
  
  
  ac.SETUP();
  delay(3);

  Serial.print(F("Free memory "));
  Serial.println(get_free_memory(), DEC);
}

//****************Main Code *********************************//

void up() {
  b.buzz(8);
}

void right() {
  ac.turnOn();
}

void down() {
  l.blink(6);
}

void left() {
  ac.turnOff();
}

void loop()
{

  /*dealing with the setup button*/
  if (digitalRead(PUSH_BUTTON) == 1) {
    lastTime = currentTime;
    while (millis() - lastTime < 3000 && digitalRead(PUSH_BUTTON) == 1) {
    }
    if (digitalRead(PUSH_BUTTON) == 1) {
      s.writeLcd("SETUP MODE");
      beep(6);//su mode
      ac.editCommand();
      setupMode = true;
      //end setup
      delay(4000);
      s.writeLcd("SETUP End");
      delay(5000);
      setupMode = false;

    } else {
      //go away
    }
  }

  /*lcd screen sve power mode*/
  currentTime = millis();
  if (currentTime - lastTime >= LCD_DELAY_TIME && !setupMode) {
    s.screenSleep();
  }


  /*Joystick deal with*/
  xData = analogRead(X_PIN);   //TODO  - mapping the analog value to 8/16/32 bit https://www.arduino.cc/reference/en/language/functions/math/map/
  yData = analogRead(Y_PIN);

  if (xData > 800 && currentDirection != 'R') {
    lastTime = currentTime;
    beep(2);
    currentDirection = 'R';
    s.writeLcd("Right");
    right();
  }
  else if (xData < 200 && currentDirection != 'L') {
    lastTime = currentTime;
    beep(2);
    currentDirection = 'L';
    s.writeLcd("Left");
    left();
  }
  else if (yData < 200 && currentDirection != 'U') {
    lastTime = currentTime;
    beep(2);
    currentDirection = 'U';
    s.writeLcd("Up");
    up();
  }
  else if (yData > 800 && currentDirection != 'D') {
    lastTime = currentTime;
    beep(2);
    currentDirection = 'D';
    s.writeLcd("Down");
    down();
  }
  currentDirection != 'N';
}
