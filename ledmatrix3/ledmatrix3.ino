//Binary Clock Using LED Matrix

#include <LedControl.h>

LedControl lc=LedControl(12,11,10,1);
// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219

int c[8] = {0,0,28,15,0,0,0,0};
int max[8] = {100,60,60,24,0,0,0,0};

void setup(){
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
//  for (int i=0; i<8;i++) {
//    c[i]=0;
//  }
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
  c[0]++;
  for (int i=0; i<8; i++){
    lc.setColumn(0,i,c[i]);
    if (c[i] > max[i]){
      c[i] = 0;
      if (i<7) {
        c[i+1]++;
      }
    }
  }
  delay(10);
}


