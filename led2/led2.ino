//Arduino LED test code:
int redpin = 11; // select the pin for the red LED
int bluepin = 9; // select the pin for the blue LED
int greenpin = 10 ;// select the pin for the green LED
int val,pin;

void setup() {
    pinMode(redpin, OUTPUT);
    pinMode(bluepin, OUTPUT);
    pinMode(greenpin, OUTPUT);
    Serial.begin (9600);
}

void loop() {
  for (pin = 11; pin>8; pin--) {
    for (val = 255; val>0; val--) {
        analogWrite(pin, val);
        delay(1);
    }
    analogWrite(pin, 0);
    Serial.println(val, DEC);
  }
    
}

