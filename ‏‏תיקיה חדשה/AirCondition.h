#include <IRremote.h>
#ifndef AirCondition_h
#define AirCondition_h


class AirCondition
{
  private:
    IRrecv *irrecv;
    IRsend irsend;
    int khz = 38; // 38kHz carrier frequency for the NEC protocol
    unsigned int * irSignal;
    unsigned int *restoredIR_Array;
    int restoredIR_ArrayLength;


  public:
    AirCondition();
    void SETUP();
    void turnAC(int state);
    void editCommand();
};

extern AirCondition ac;

#endif
