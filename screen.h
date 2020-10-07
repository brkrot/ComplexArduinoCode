#include <LiquidCrystal_I2C.h>
#ifndef screen_h
#define screen_h

class screen
{
  private:
  LiquidCrystal_I2C *lcdPointer;
  public:
    screen();
    void SETUP();
    void writeLcd(String text);
    void screenSleep();
};

extern screen s;

#endif
