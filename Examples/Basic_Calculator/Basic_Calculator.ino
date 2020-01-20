#include <Wire.h>
#include "Keypad_I2C.h"
#include "LCD_I2C.h"
#include <stdlib.h>
#include <stdio.h>

#define I2CADDR 0x27 // default address
#define TRUE 1
#define FALSE 0

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
  lcd.print("Welcome to MyCal");
  lcd.setCursor(0,1); 
}

float Result;  
float Num1,Num2;
String FirstNum;
String SecondNum;
char Operator;
boolean NewCal = FALSE;
boolean FirstNumber = FALSE; // false is first number, true is second number 

float StrToFloat(String Str){
  char temp[10];
  strcpy(temp,Str.c_str());
  return atof(temp); 
}

void loop() {
  
  if (NewCal){  // Get ready for New Calcultaion and clear the LCD
    FirstNum = "0";
    SecondNum = "0";
    Operator="";
    FirstNumber = FALSE;
    lcd.clear();
    lcd.print("Welcome to MyCal");
    lcd.setCursor(0,1); 
    NewCal = FALSE;
  }

  while (!NewCal)
  {
    char key = keypad.getKey();
    if (key){
    if (key=='/'|| key=='*' || key=='+' || key=='-' )
    {
      Operator = key;
      FirstNumber = TRUE;
    }

    if (key=='=') // start calculation and wait for new key to start new calculation
    {
        lcd.print(key);

        // convert FirstNum and SecondNum into float
        Num1 = StrToFloat(FirstNum);
        Num2 = StrToFloat(SecondNum);

        // Do the calculation and saved into result
        if (Operator== '/') Result = Num1 / Num2 ;
        if (Operator== '*') Result = Num1 * Num2 ;
        if (Operator== '-') Result = Num1 - Num2 ;
        if (Operator== '+') Result = Num1 + Num2 ;

        // Display the result on the LCD
        lcd.print(Result);
        
        // wait until any key is pressed   
        while(!keypad.getKey());
        NewCal = TRUE; 
    }

    // take only numeric characters
    if (key=='0' || key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || 
        key=='6' || key=='7' || key=='8' || key=='9' || key=='.')
      {
        if (!FirstNumber) {FirstNum += key;  }
                     else {SecondNum += key; }    
      }
    lcd.print(key);
    }
  }
} 