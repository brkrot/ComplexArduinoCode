#include <IRremote.h>
#include <EEPROM.h>
#include "Arduino.h"
#include "AirCondition.h"
#include "screen.h"

/*********************Constants*********************************/
#define IR_ON_LENGTH_2BYTE_PER_INT 400    //This is the location of the length. Remember that each int =2 bytes 
#define IR_ON_ADDRESS 402
/*********************Ports*********************************/
#define IR_RECEIVE_PIN 11

//Ctor
AirCondition::AirCondition() {

  *irrecv = IRrecv(IR_RECEIVE_PIN);
  unsigned int tempIrSignal[] = { 8950, 4400, 550, 500, 600, 500, 600, 450, 600, 500, 600, 500, 550, 500, 600, 500, 600, 500, 550, 1600, 600, 1550, 600, 1550, 600, 500, 600, 1550, 600, 500, 600, 500, 550, 500, 600, 1600, 550, 1600, 600, 450, 600, 1600, 550, 500, 600, 500, 600, 500, 550, 500, 600, 500, 600, 500, 550, 500, 600, 500, 600, 1550, 600, 500, 550, 500, 600, 500, 600, 500, 550, 500, 600, 1600, 550, 1600, 550, 500, 600, 500, 600, 500, 550, 500, 600 };
  irSignal = tempIrSignal;


}
//setup function
void AirCondition::SETUP() {
  
}

void AirCondition::turnOn() {
  s.writeLcd(F("AC ON"));

  //Creating an array from the data in the memory
  int recoverdOnIrSignal[EEPROM.read(IR_ON_LENGTH_2BYTE_PER_INT)];                  //EEPROM.read(IR_ON_LENGTH_2BYTE_PER_INT) is the size of the signal's array
  //read the data itself from the memory
  readIntArray( IR_ON_ADDRESS,  recoverdOnIrSignal, sizeof(recoverdOnIrSignal) / sizeof(recoverdOnIrSignal[0]));  //IR_ON_ADDRESS is the adress where the code starts
  /*
    //Sending the command as raw data
    irsend->sendRaw(recoverdOnIrSignal, sizeof(recoverdOnIrSignal) / sizeof(recoverdOnIrSignal [0]), khz);

  */

}
void AirCondition::turnOff() {
  s.writeLcd(F("AC OFF"));
}
void AirCondition::editCommand() {
  s.writeLcd(F("EDIT MODE"));
  s.writeLcd(F("on-R|off-L"));
}

/*EEPROM write FUNCTION*/
void AirCondition::writeIntArray(int address, int numbers[], int arraySize)
{
  int addressIndex = address;
  for (int i = 0; i < arraySize; i++)
  {
    EEPROM.put(addressIndex, numbers[i]);
    addressIndex += sizeof(int);
  }
}
/*EEPROM READ FUNCTION*/
void AirCondition::readIntArray(int address, int numbers[], int arraySize)
{
  int addressIndex = address;
  for (int i = 0; i < 60; i++)
  {
    EEPROM.get(addressIndex, arr[i]);
      addressIndex += sizeof(int);
  }

}

AirCondition ac = AirCondition();
