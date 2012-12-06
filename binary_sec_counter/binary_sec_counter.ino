/*
Binary Second Counter
 
 Created Alastair Montgomery 22/11/2012
 
 */

int ledPins[] = {
  7,8,9,10,11,12};
int mask[] = {
  1,2,4,8,16,32};
int ledCount = 6;

void setup() {
  for (int thisPin =0; thisPin < ledCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }
}

void loop() {
  int seconds = 0;
  for (int thisPin =0; thisPin < ledCount; thisPin++){
    if (seconds & mask[thisPin]) {
      digitalWrite(ledPins[thisPin], HIGH);
    }
    else {
      digitalWrite(ledPins[thisPin], LOW);
    }
  }
  delay(1000);
  seconds++;
  if (seconds >= 60) seconds = 0;
}

