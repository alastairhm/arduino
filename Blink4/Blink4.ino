
int numLed = 10;
int ledpins[] = {
  13,12,11,10,9,8,7,6,5,4};
int mask[] = {
  1,2,4,8,16,32,64,128,256,512};
int counter = 0;
int row = 1;

void setup() {                
  // initialize the digital pin as an output.
  digitalWrite(row,OUTPUT);
  digitalWrite(row,LOW);
  for (int i=0;i<numLed;i++){
    pinMode(ledpins[i], OUTPUT);
    digitalWrite(ledpins[i], HIGH);
    delay(250);
  }
  Serial.begin(9600);
}

void loop() {

  for (int i=0;i<numLed;i++){
    if (counter & mask[i]) {
      digitalWrite(ledpins[i], HIGH);
    }
    else {
      digitalWrite(ledpins[i], LOW);
    }   
  }

  delay(500);
  counter++;
  Serial.println(counter);
}


