
#ifndef led_h
#define led_h


class led
{
  public:
    led();
    void SETUP();
    void blink(int times);
};

extern led l;

#endif
