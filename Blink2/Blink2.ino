
int led1 = 8;
int led2 = 9;
int counter = 0;

void setup() {                
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);  
}

void loop() {

  if (counter & 1) {
    digitalWrite(led1, HIGH);
  }
  else {
    digitalWrite(led1, LOW);
  }

  if (counter & 2) {
    digitalWrite(led2, HIGH);
  }
  else {
    digitalWrite(led2, LOW);
  }
  delay(1000);
  counter++;

}

