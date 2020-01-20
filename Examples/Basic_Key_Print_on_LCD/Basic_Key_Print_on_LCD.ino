#include <Wire.h>
#include "Keypad_I2C.h"
#include "LCD_I2C.h"

#define I2CADDR 0x27 // default address

const byte ROWS = 4; 
const byte COLS = 4; 
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
LCD_I2C lcd(I2CADDR);

void setup() {
  
  keypad.begin( );  

  lcd.begin(16, 2);
  lcd.display();
  lcd.clear();
  lcd.print("Hello, My world!");
  lcd.setCursor(0,1); 
  lcd.print("Key : ");
}


void loop() {

   char key = keypad.getKey();
  
  if (key){ lcd.setCursor(6,1); lcd.print(key);  }

}
