// Auto scroll a message on the LCD and receive new messages via Serial port.
// Alastair Montgomery (c) 2013
// Version 1.00
 
// include the library code:
#include <LiquidCrystal.h>
#include <string.h>

// initialize the library with the numbers of the interface pins
// below for SainSmart LCD Shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Default Message
char msg[256] = "Serial Message Version 1.00";
char buffer[256];
int newMsg = true;
int scrollAmount = 0;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop() {
  
  //Read serial
  if (Serial.available()){
    delay(100);
    int i = 0;
    while (Serial.available() > 0 && i<254){
      buffer[i++] = Serial.read();
    }
    buffer[i] = '\0';
    strcpy(msg,buffer);

    newMsg = true;
  }
 
  if (newMsg){
    lcd.noAutoscroll();
    lcd.clear();
    scrollAmount = strlen(msg)-16;
    newMsg = false;
    lcd.setCursor(0, 0);  
    lcd.print("***New Message***");    
  }
  
  // set the cursor to (0,1):
  lcd.setCursor(0, 1);  
  lcd.print(msg);
  delay(500);

  // set the cursor to (16,1):
  lcd.setCursor(16,0);
  // set the display to automatically scroll:;
  lcd.autoscroll();
  //lcd.noAutoscroll();
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < scrollAmount+16; thisChar++) {
    lcd.print(" ");
    delay(700);
  }
  
  // turn off automatic scrolling
  lcd.noAutoscroll();  
  // clear screen for the next loop:
  lcd.clear();
}

