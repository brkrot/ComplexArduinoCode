/********************* Includes ***************************/
#include <IRremote.h>
#include <EEPROM.h>

/*********************Constants*********************************/

#define LCD_DELAY_TIME 5000
#define JOYSTICK_RIGHT_THRSHOLD 800
#define JOYSTICK_LEFT_THRSHOLD 200
#define JOYSTICK_UP_THRSHOLD 800
#define JOYSTICK_DOWN_THRSHOLD 200
/*********************Ports*********************************/
/*X Y are oposite than what written on the joystick cause that is how it makes sense with the axis direction*/
#define X_PIN A1                //Naming all the used PINs
#define Y_PIN A0
#define BUZZER 7
//#define IR_RECEIVE_PIN 11
#define PUSH_BUTTON 12
#define DEBUG 1
#define FUNC_TAGS 1

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


  Serial.begin(9600);

#if DEBUG==1 && FUNC_TAGS==1
  // Serial.begin(115200);
  Serial.println(F("***ComplexArduinoCode.setup - begin"));
#endif
  //initLcd();    //Initializing the lcd screen
  beep(2);    //A beep to let the user know the system is up

  pinMode(PUSH_BUTTON, INPUT);
  pinMode(BUZZER, OUTPUT);
  /*#if DEBUG==1
    Serial.print(F("Free memory "));
    Serial.println(get_free_memory(), DEC);
    Serial.print(F("Free memory "));
    Serial.println(get_free_memory(), DEC);
    #endif*/
  setupEEPROM();
  setupLcd();
  setupAirCondition();
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***ComplexArduinoCode.setup - end"));
#endif
}
//****************Main Code *********************************//

void up() {
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***ComplexArduinoCode.up - begin"));
#endif

  // b.buzz(3);
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***ComplexArduinoCode.up - end"));
#endif
}

void right() {
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***ComplexArduinoCode.right - begin"));
#endif
  turnAC(1);
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***ComplexArduinoCode.right - end"));
#endif
}

void down() {
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***ComplexArduinoCode.down - begin"));
#endif
  //turnAC(1);
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***ComplexArduinoCode.down - end"));
#endif
}

void left() {
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***ComplexArduinoCode.left - begin"));
#endif
  turnAC(0);
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***ComplexArduinoCode.left - end"));
#endif
}

void loop()
{
  if (!Serial) {
    Serial.begin(115200);
  }
  /*dealing with the setup button*/
  if (digitalRead(PUSH_BUTTON) == 1) {
    lastTime = currentTime;
    while (millis() - lastTime < 3000 && digitalRead(PUSH_BUTTON) == 1) {
    }
    if (digitalRead(PUSH_BUTTON) == 1) {
      writeLcd("SETUP MODE");
      beep(6);//su mode
      setupMode = true;
      editCommand();
      writeLcd("SETUP End");
      setupMode = false;
    } else {
      //go away
    }
  }

  /*lcd screen sve power mode*/
  currentTime = millis();
  if (currentTime - lastTime >= LCD_DELAY_TIME && !setupMode) {
    sleepLcd();
    currentDirection = 'N';
  }


  /*Joystick deal with*/
  xData = analogRead(X_PIN);   //TODO  - mapping the analog value to 8/16/32 bit https://www.arduino.cc/reference/en/language/functions/math/map/
  yData = analogRead(Y_PIN);
#if DEBUG==1
  /*Serial.print(F("("));
    Serial.print(xData);
    Serial.print(F(","));
    Serial.print(yData);
    Serial.println(F(")"));*/
#endif

  if (!setupMode) {     //Check the Joystick status only if you are not in setup mode
    if (xData > JOYSTICK_RIGHT_THRSHOLD /*&& xData > yData*/ && currentDirection != 'R') {
      lastTime = currentTime;
      beep(2);
      currentDirection = 'R';
      writeLcd("Right");
      right();
    }
    else if (xData < JOYSTICK_LEFT_THRSHOLD /*&& xData < yData*/ && currentDirection != 'L') {
      lastTime = currentTime;
      beep(2);
      currentDirection = 'L';
      writeLcd("Left");
      left();
    }
    else if (yData > JOYSTICK_UP_THRSHOLD /*&& yData > xData*/ && currentDirection != 'U') {
      lastTime = currentTime;
      beep(2);
      currentDirection = 'U';
      writeLcd("Up");
      up();
    }
    else if (yData < JOYSTICK_DOWN_THRSHOLD /*&& yData < xData*/ && currentDirection != 'D') {
      lastTime = currentTime;
      beep(2);
      currentDirection = 'D';
      writeLcd("Down");
      down();
    }
  }
}
