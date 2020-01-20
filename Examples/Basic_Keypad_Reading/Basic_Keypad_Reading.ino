// Basic Keypad Reading
// When any key is pressed will be shown in Serial Monitor

#include <Wire.h>
#include "Keypad_I2C.h"

#define I2CADDR 0x27  // default address

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','*'},
  {'4','5','6','/'},
  {'7','8','9','-'},
  {'.','0','=','+'}
};

// Pin connections on MCP23017 for keys
 byte rowPins[] = {3,2,1,0}; 
 byte colPins[] = {4,5,6,7}; 
 
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS,I2CADDR);

void setup() {
  Serial.begin(9600);
  keypad.begin( );
}


void loop() {
   char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
  }
}
