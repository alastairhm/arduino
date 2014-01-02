// Auto scroll a message on the LCD and receive new messages via Serial port.
// Alastair Montgomery (c) 2013
// Version 1.03

// include the library code:
#include <LiquidCrystal.h>
#include <string.h>

// initialize the library with the numbers of the interface pins
// below for SainSmart LCD Shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int ledWidth = 16;
const int ledDepth = 2;

//Default Message
char msg[256] = "Serial Message Version 1.03";
char info[256] = "New Message";
char buffer[256];
int newMsg = true;
int previous[ledDepth] = {
  0};
int pos[ledDepth] = {
  0};

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(ledWidth,ledDepth);
  Serial.begin(9600);
}

void printLine(int refreshSeconds, int lineNum, char message[]){
  //Check if the current second since restart is a mod of refresh seconds , 
  //if it is then update the display , it must also not equal the previously 
  //stored value to prevent duplicate refreshes
  if((millis()/1000) % refreshSeconds == 0 && previous[lineNum] != (millis()/1000)){
    previous[lineNum] =  (millis()/1000);  //Store the current time we entered for comparison on the next cycle
    lcd.setCursor(0, lineNum);    //Set our draw position , set second param to 0 to use the top line
    char lcdTop[ledWidth];              //Create a char array to store the text for the line
    int copySize = ledWidth;            // What is the size of our screen , this could probably be moved outside the loop but its more dynamic like this
    if(strlen(message) < copySize)
    {
      //if the msg is smaller than the current buffer use its length instead;
      copySize = strlen(message)+1;
    }
    //Store the current position temporarily and invert its sign if its negative since we are going in reverse
    int tempPos = pos[lineNum];
    if(tempPos < 0)
    {
      tempPos = -(tempPos);
    }
    //Build the lcd text by copying the required text out of our template msg variable 
    memcpy(&lcdTop[0],&message[tempPos],copySize);
    lcd.print(lcdTop);            //Print it from position 0
    //Increase the current position and check if the position + 16 (screen size) would be larger than the msg length , if it is go in reverse by inverting the sign.
    if (copySize == ledWidth){
      pos[lineNum] += 1;
      if(pos[lineNum] +copySize >= strlen(msg))
      {
        pos[lineNum] = -(pos[lineNum]);
      }
    }
  }
}

int serialRead(char message[]) {
  int flag = false;

  //Read serial
  if (Serial.available()){
    delay(100);
    int i = 0;
    while (Serial.available() > 0 && i<254){
      buffer[i++] = Serial.read();
    }
    buffer[i] = '\0';
    strcpy(message,buffer);
    flag = true;
  }
  return flag;  
}

void loop() {

  newMsg = serialRead(msg);

  if (newMsg){
    lcd.noAutoscroll();
    lcd.clear();
    newMsg = false;
    strcpy(info,"New Message"); 
    pos = {0,0};     
  }

  printLine(1,0,info);
  printLine(1,1,msg);
}


