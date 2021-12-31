
/* 
   DE6102 AutoScan V4 
   by Stephen Julian
   This work is published under the MIT licence.
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keyboard.h>

String topLine = "AutoScan";
String bottomLine = "  IDLE  ";
LiquidCrystal_I2C lcd(0x27,8,2);

void setup() {
  lcd.init();
  //lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(topLine);
  lcd.setCursor(0,1);
  lcd.print(bottomLine);
  Keyboard.begin();
  //Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if(Serial1.available()) {
    String rxString = Serial1.readString();
    //lcd.setCursor(0,1);
    //lcd.print("ÿep");
    bool pickNumberIsNotFound = true;
    int stringIndex = 0;
    int pickNumberStart = rxString.indexOf("----",stringIndex); // returns -1 if no index
    if(pickNumberStart != -1) {
      while(pickNumberIsNotFound) {
        pickNumberStart = pickNumberStart + 1;
        int pickNumberDigit1 = pickNumberStart;
        char pickNumberChar1 = rxString[pickNumberDigit1];
        if(isDigit(pickNumberChar1)) {
          int pickNumberDigit2 = pickNumberDigit1 + 1;
          char pickNumberChar2 = rxString[pickNumberDigit2];
          if(isDigit(pickNumberChar2)) {
            int pickNumberDigit3 = pickNumberDigit2 + 1;
            char pickNumberChar3 = rxString[pickNumberDigit3];
            if(isDigit(pickNumberChar3)) {
              int pickNumberDigit4 = pickNumberDigit3 + 1;
              char pickNumberChar4 = rxString[pickNumberDigit4];
              String outputString = "";
              outputString.concat(pickNumberChar1);
              outputString.concat(pickNumberChar2);
              outputString.concat(pickNumberChar3);
              if(isDigit(pickNumberChar4)) {
                outputString.concat(pickNumberChar4);
              }
              int numChars = outputString.length();
              if(numChars == 3) {
                topLine = "  #";
                topLine.concat(outputString);
                topLine.concat("  ");
              } else { // numChars == 4
                topLine = " #";
                topLine.concat(outputString);
                topLine.concat("  ");
              }
              
              if(outputString.length() < 4) {
                outputString.concat('!');
              }
              //delay(3000); // delay for use only when testing
              Keyboard.print(outputString);
              lcd.setCursor(0,0);
              lcd.print(topLine);
              //lcd.print("12345670");
              lcd.setCursor(0,1);
              lcd.print(" SERVED ");
              pickNumberIsNotFound = false;
            }
          }
        }
      }
    }
  }
}
