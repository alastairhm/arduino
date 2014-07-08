/*
  Blink Sink
  
  Turns on an two LEDs on then off, repeatedly, by multiplexing.
  Instead of connecting the LEDs to a common ground they are connected to separate "sink" pins.
  Setting these pins to LOW turn the LED on, HIGH turns it off.
  
  Using this method you can add extra leds to each row by connecting them from another digital pin
  to the common sink pin.
 
  November 2012
  Alastair Montgomery
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
// Give the sink pins names
int row1 = 8;
int row2 = 7;
// delay for multiplex, reduce to get both LEDs to appear to be lite at same time
int wait = 100;

// the setup routine runs once when you press reset:
void setup() {           
  // initialize the sink pins, set as low (GND).
  pinMode(row1,OUTPUT);
  digitalWrite(row1,LOW);  
  pinMode(row2,OUTPUT);
  digitalWrite(row2,LOW);
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);  
  digitalWrite(led,HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(row1, HIGH);   // turn the first LED off  by making the voltage HIGH
  digitalWrite(row2, LOW);    // turn the second LED on  by making the voltage LOW
  delay(wait);                 // wait for a bit
  digitalWrite(row2, HIGH);   // turn the second LED off  by making the voltage HIGH
  digitalWrite(row1, LOW);    // turn the first LED on by making the voltage LOW
  delay(wait);                 // wait for a bit
}
