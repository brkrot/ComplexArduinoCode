#include <IRremote.h>
#ifndef AirCondition_h
#define AirCondition_h


class AirCondition
{
  private:
    IRrecv *irrecv;
    IRsend *irsend;
    int khz = 38; // 38kHz carrier frequency for the NEC protocol
    unsigned int * irSignal;
    int arr[60];


  public:
    AirCondition();
    void SETUP();
    void turnOn();
    void turnOff();
    void editCommand();
    void readIntArray(int address, int numbers[], int arraySize);
    void writeIntArray(int address, int numbers[], int arraySize);
};

extern AirCondition ac;

#endif
