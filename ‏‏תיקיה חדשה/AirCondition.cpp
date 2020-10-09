#include <IRremote.h>
#include <EEPROM.h>
#include "Arduino.h"
#include "AirCondition.h"


/*********************Constants*********************************/
#define IR_ON_LENGTH_2BYTE_PER_INT 0    //This is the location of the length. Remember that each int =2 bytes 
#define IR_ON_ADDRESS 2

# define DEBUG
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

#ifdef DEBUG
  Serial.begin(9600);
  Serial.println(F("Debugging mode in AirCondition:"));
#endif
  EEPROM.write(0, 32);
  restoredIR_ArrayLength = 32;
}

void AirCondition::turnAC(int state) {


 

  //Creating a temp array for the data from the EEPROM
  restoredIR_Array = new unsigned int[EEPROM.read(IR_ON_LENGTH_2BYTE_PER_INT)];
  restoredIR_ArrayLength = EEPROM.read(IR_ON_LENGTH_2BYTE_PER_INT);

#ifdef DEBUG
  Serial.println(F("The size of the array is:"));
  Serial.println(restoredIR_ArrayLength);
  Serial.println(F("Values are:"));
  for (int i = 0; i < restoredIR_ArrayLength; i ++) {
    Serial.println(restoredIR_Array[i]);
  }
#endif

  unsigned int temp;
  for (int i = 0; i < restoredIR_ArrayLength / 2; i++) {
    EEPROM.get(i * 2, temp);
    restoredIR_Array[i] = temp;
  }

#ifdef DEBUG
  Serial.println(F("The size of the array is:"));
  Serial.println(restoredIR_ArrayLength);
  Serial.println(F("Values are:"));
  for (int i = 0; i < restoredIR_ArrayLength; i ++) {
    Serial.println(restoredIR_Array[i]);
  }
#endif
  irsend.sendRaw(restoredIR_Array, restoredIR_ArrayLength, khz); // Note the approach used to automatically calculate the size of the array.
  delete restoredIR_Array;
  

}

void AirCondition::editCommand() {
#ifdef DEBUG
  Serial.println(F("EDIT MODE - begins"));
#endif

  /*bool run = true;
  while (run) {
    decode_results results;        // Somewhere to store the results

    if (irrecv.decode(&results)) {  // Grab an IR code

      dumpRaw(&results);            // Output the results in RAW format
      dumpCode(&results);           // Output the results as source code
      Serial.println("");           // Blank line between entries
      irrecv.resume();              // Prepare for the next value
      run = false;
    }
*/
//Serial.print() 
  }


AirCondition ac = AirCondition();
