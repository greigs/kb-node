/*
  Relays data back to the raspberry pi from the USB serial to HW serial
  while silmutaneously recieving key commands from the HW serial for emulating
  a keyboard.
*/

void setup() {
  // start + wait for serial debug in/output
  while (!Serial);
  Serial.begin(115200);
  Serial.println(F("Ready"));

  // Sends a clean report to the host. This is important because
  // the 16u2 of the Uno/Mega is not turned off while programming
  // so you want to start with a clean report to avoid strange bugs after reset.
  Keyboard.begin();
}

byte data = -1;
byte firstCommandByte = -1;
byte secondCommandByte = -1;
char key = -1;
char commandPerc = 37;
int bytecount = 0;
char keys[] = {0,0,0,0,0,0};

void loop() {
  
  if (Serial.available()) {
    // recieve a command, ending with a new line character
    while (data != '\n' ) {
      bool sendToHWSerial = false;
      if (Serial.available()){
          data = Serial.read();
          if (bytecount == 0){
            firstCommandByte = data;
          }
          else if (bytecount == 1){
            secondCommandByte = data;
            if (firstCommandByte == commandPerc && secondCommandByte == 'w'){
              sendToHWSerial = true;
              Serial.println(F("Sending data to HW Serial"));
            }
          }
          else if (bytecount == 2){
            key = data;
          }
          if (data != -1) {
            //Serial.write(data);
            if (bytecount > 1 && sendToHWSerial){
              // send to HW serial
            }
          }
          bytecount++;
      }
    }
    if (firstCommandByte == commandPerc){
      Serial.println(F("Finished Processing Command"));
      
      if (secondCommandByte == 'd'){
        //Serial.println(F("Sending Key in 2 seconds"));
        addToKeyList(key);
        pressRawKeyboard(0, 
        keys[0] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[0]),
        keys[1] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[1]),
        keys[2] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[2]),
        keys[3] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[3]),
        keys[4] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[4]),
        keys[5] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[5]));
      } else if (secondCommandByte == 'u'){
        //Serial.println(F("Removing Key in 2 seconds"));
        removeKeyFromList(key);
        pressRawKeyboard(0, 
        keys[0] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[0]),
        keys[1] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[1]),
        keys[2] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[2]),
        keys[3] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[3]),
        keys[4] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[4]),
        keys[5] == 0 ? 0 : RAW_KEYBOARD_KEY(keys[5]));
      }
    } else if (firstCommandByte != -1){
      Serial.println(F("Unknown Command"));
    }
    
    bytecount = 0;
    data = -1;
    firstCommandByte = -1;
    secondCommandByte = -1;
    key = -1;   
  }
}

void addToKeyList(char key){
  bool found = false;
  for (int i=0; i< 6; i++){
    if (keys[i] == key){
      found = true;
      break;
    }
  }
  if (!found){
    for (int i=0; i< 6; i++){
      if (keys[i] == 0){
        keys[i] = key;
        break;
      }
    }
  }  
}

void removeKeyFromList(char key){
  for (int i=0; i< 6; i++){
    if (keys[i] == key){
      keys[i] = 0;
      break;
    }
  }  
}

void pressRawKeyboard(uint8_t modifiers, uint8_t key1, uint8_t key2, uint8_t key3, uint8_t key4, uint8_t key5, uint8_t key6) {
  uint8_t keys[8] = {
    modifiers, 0, key1, key2, key3, key4, key5, key6
  }; //modifiers, reserved, key[0]
  HID_SendReport(HID_REPORTID_KEYBOARD, keys, sizeof(keys));
}
