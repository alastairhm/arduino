Blink Sink
  
  Turns on an two LEDs on then off, repeatedly, by multiplexing.
  Instead of connecting the LEDs to a common ground they are connected to separate "sink" pins.
  Setting these pins to LOW turn the LED on, HIGH turns it off.
  
  Using this method you can add extra leds to each row by connecting them from another digital pin
  to the common sink pin.
  For example to control two rows of 5 LEDs you'd need just 7 Digital I/O pins.

  If the delay between enabling the rows is low enough both rows appear to be lit at the same time.
 
  November 2012
  Alastair Montgomery