#include <LedControl.h>

struct cgr { 
char c;
byte d[5];
};


static cgr _digits[10] =
{
'0', { 0x2, 0x5, 0x5, 0x5, 0x2 },
'1', { 0x2, 0x6, 0x2, 0x2, 0x7 },
'2', { 0x6, 0x1, 0x2, 0x4, 0x7 },
'3', { 0x6, 0x1, 0x2, 0x1, 0x6 },
'4', { 0x1, 0x5, 0x7, 0x1, 0x1 },
'5', { 0x7, 0x4, 0x6, 0x1, 0x6 },
'6', { 0x3, 0x4, 0x6, 0x5, 0x2 },
'7', { 0x7, 0x1, 0x2, 0x2, 0x2 },
'8', { 0x2, 0x5, 0x2, 0x5, 0x2 },
'9', { 0x2, 0x5, 0x3, 0x1, 0x6 },
};

int row=0;

LedControl lc=LedControl(12,11,10,1);
// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219

void setup(){
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);

    for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,true);
      lc.setLed(1,col,row,false);
      delay(5);
    }
  }

  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,false);
      lc.setLed(1,col,row,true);
      delay(5);
    }
  }
}

void loop(){
  for (int i=0; i<99; i++){
    for (int j=0 ; j<5; j++) {
       row = (_digits[i / 10].d[j] << 4) | _digits[i % 10].d[j];
       
       lc.setRow(0,j,row);
    }
    delay(500);
  }
}


