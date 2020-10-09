

/*********************Constants*********************************/
#define IR_ON_SIZE 0
#define IR_ON_ADDRESS 2
#define IR_OFF_SIZE 322
#define IR_OFF_ADDRESS 324

/*********************Ports*********************************/

IRsend irsend;
int khz = 38; // 38kHz carrier frequency for the NEC protocol
int restoredIR_ArrayLength;
int savedIrONLength;
int savedIrOFFLength;
unsigned int* savedIrON;
unsigned int* savedIrOFF;

/**
	  Setup all the needs
*/
void setupAirCondition() {
#if DEBUG==1
  Serial.println(F("Debugging mode in AirCondition:"));
#endif
  savedIrON = NULL;
  savedIrOFF = NULL;
  savedIrONLength = EEPROM.read(IR_ON_SIZE);
  savedIrOFFLength = EEPROM.read(IR_OFF_ADDRESS);
}


/**
	  Print the result (second argument) as Pronto Hex on the Stream supplied as argument.
	  @param state tells us whether we wnat to turn ON (state=1) or OFF (state=2)
*/
void turnAC(int state) {
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***AirConditionHelper.turnAC - begin"));
#endif
#if DEBUG==1
  printEeprom();
#endif

  //temp variables
  int * arrPointer ;
  int arrSize;
  int dataAddressInMemory;

  if (state == 1) { //ON
    arrPointer = savedIrON;
    arrSize = savedIrONLength;
    dataAddressInMemory = IR_ON_ADDRESS;
  } else {   //OFF
    arrPointer = savedIrOFF;
    arrSize = savedIrOFFLength;
    dataAddressInMemory = IR_OFF_ADDRESS;
  }


  //In case of a new ir Code we need to get its length and to read the memory with the data
  if (arrPointer == NULL) {
    arrPointer = new unsigned int[arrSize];


    //Now we need the original pointers to hild the right adress
    if (state == 1) { //ON
      savedIrON = arrPointer ;
    } else {   //OFF
      savedIrOFF = arrPointer;
    }

    //Reading the data into our allocated array - arrPointer
    readIntArray(dataAddressInMemory, arrPointer, arrSize);
  }
#if DEBUG==1
  if (state == 1) {
    Serial.print(F("savedIrON ["));
  } else {
    Serial.print(F("savedIrOFF ["));
  }
  Serial.print(arrSize);
  Serial.println(F("] = {"));
  for (int i = 0; i < arrSize; i++) {
    Serial.print(arrPointer[i]);
    Serial.print(",");
  }
  Serial.println("}");
#endif
  irsend.sendRaw(arrPointer, arrSize, khz); // Note the approach used to automatically calculate the size of the array.


  arrPointer = NULL;
  arrSize = -1;
  dataAddressInMemory = -1;

#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***AirConditionHelper.turnAC - end"));
#endif
}

void editCommand() {
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***AirConditionHelper.editCommand - begin"));
#endif


  writeLcd(F("R-on L - off"));
  char zone = 'C';
  do {
    xData = analogRead(X_PIN);
    if (xData > JOYSTICK_RIGHT_THRSHOLD ) {
      beep(2);
      zone = 'R';
      writeLcd("Right - on");
      delete savedIrON;
      savedIrON = NULL;
    }
    else if (xData < JOYSTICK_LEFT_THRSHOLD) {
      beep(2);
      zone = 'L';
      writeLcd("Left - off");
      delete savedIrOFF;
      savedIrOFF = NULL;
    }
  } while (zone == 'C');

#if DEBUG==1
  Serial.println(F("The chozen dir to edit is:"));
  if (zone == 'R') {
    Serial.println(F("Right side - On - command"));
  } else {
    Serial.println(F("Left - Off - command"));
  }
#endif

  delay(2000);
  setupRec();
  if (zone == 'R') {
    recordIr(1);
  } else {
    recordIr(0);
  }
#if DEBUG==1 && FUNC_TAGS==1
  Serial.println(F("***AirConditionHelper.editCommand - end"));
#endif
}
