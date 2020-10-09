
#include <LiquidCrystal_I2C.h>
//#include <Wire.h>
#include "Arduino.h"
#include "screen.h"

//Ctor
screen::screen() {
  *lcdPointer = LiquidCrystal_I2C(0x27, 20, 4);
}
//setup function
void screen::SETUP() {
  LiquidCrystal_I2C lcd = *lcdPointer;
  lcd.init();       // initialize the lcd
  lcd.backlight();  //Turn the lcd light - ON
  lcd.clear();      //Clear The text on the lcd
  lcd.print(F("Welcome to"));
  lcd.setCursor(0, 1);
  lcd.print(F("Milbat #Patient"));
}

//write to the screen
void screen::writeLcd(String text) {
  LiquidCrystal_I2C lcd = *lcdPointer;
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.clear();
  //lcd.print(F("text"));
  lcd.print(text);
  
  /*if (text.length() <= 16) {
    lcd.print(text);
  } else {
    lcd.setCursor(0, 0);
    lcd.print(text);
    lcd.setCursor(1, 0);
    lcd.print(text.substring(16));
  }*/

  /* if (text.length() > 16) {
     for (int i = 0; i < text.length(); i++) {
       delay(250);
       lcd.scrollDisplayLeft();
     }
    }*/
}

void screen::screenSleep() {
  lcdPointer->noBacklight();
}
screen s = screen();
