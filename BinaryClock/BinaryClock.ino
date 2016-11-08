/*
Binary LED Clock Using Interupt to increment the second counter
 
 November 2012
 Alastair Montgomery
 */

int seconds = 0;
int minutes = 0;
int hours = 0;
int numLed = 10;
int numRow = 3;
int ledpins[] = {
  4,5,6,7,8,9,10,11,12,13};
int mask[] = {
  1,2,4,8,16,32,64,128,256,512};
int rows[] = {
  3,2,1};

void setup() {                
  // initialize the row digital pins as an output/low.
  for (int i=0;i<numRow;i++) {
    pinMode(rows[i],OUTPUT);
    digitalWrite(rows[i],LOW);
  }
  // initialize the digital pins as output/high check to LED working
  for (int i=0;i<numLed;i++){
    pinMode(ledpins[i], OUTPUT);
    digitalWrite(ledpins[i], HIGH);
    delay(250);
  }
  //Turn off all rows
  for (int i=0;i<numRow;i++) {
    digitalWrite(rows[i],HIGH);
  }  

  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 31250;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  if (seconds++ > 59) {
    seconds = 0;
    if (minutes++ > 59) {
      minutes = 0;
      if (hours++ > 23) hours = 0;
    }
  }
}

void writeRow(int rowWrite, int value){
  //Enable the row by setting its pin to LOW, all other rows to HIGH
  for (int i=0;i<numRow;i++){
    if ( i == rowWrite) {
      digitalWrite(rows[i],LOW);
    }
    else {
      digitalWrite(rows[i],HIGH);
    }
  }
  //Display value in Binary on LEDs
  for (int i=0;i<numLed;i++){
    if (value & mask[i]) {
      digitalWrite(ledpins[i], HIGH);
    }
    else {
      digitalWrite(ledpins[i], LOW);
    }   
  }	
}

void loop() {
  writeRow(0,seconds);
  writeRow(1,minutes);
  writeRow(2,hours);
}
