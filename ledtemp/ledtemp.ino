/*
Alastair Montgomery
 Temp to a LCD Matix
 */

#include <idDHT11.h>
#include <LedControl.h>


float celtemp = 0.0;
int row = 0;

//Define the 3x5 Numeric font

struct cgr {
  char c;
  byte d[5];
};

static cgr _digits[10] =
{
  '0', { 
    0x2, 0x5, 0x5, 0x5, 0x2   }
  ,
  '1', { 
    0x2, 0x6, 0x2, 0x2, 0x7   }
  ,
  '2', { 
    0x6, 0x1, 0x2, 0x4, 0x7   }
  ,
  '3', { 
    0x6, 0x1, 0x2, 0x1, 0x6   }
  ,
  '4', { 
    0x1, 0x5, 0x7, 0x1, 0x1   }
  ,
  '5', { 
    0x7, 0x4, 0x6, 0x1, 0x6   }
  ,
  '6', { 
    0x3, 0x4, 0x6, 0x5, 0x2   }
  ,
  '7', { 
    0x7, 0x1, 0x2, 0x2, 0x2   }
  ,
  '8', { 
    0x2, 0x5, 0x2, 0x5, 0x2   }
  ,
  '9', { 
    0x2, 0x5, 0x3, 0x1, 0x6   }
  ,
};

// Setup LCD Matrix
LedControl lc=LedControl(12,11,10,1);
// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219

int idDHT11pin = 2; //Digital pin for comunications
int idDHT11intNumber = 0; //interrupt number (must be the one that use the previus defined pin (see table above)

//declaration
void dht11_wrapper(); // must be declared before the lib initialization

// Lib instantiate
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);

void setup()
{
  Serial.begin(9600);
  Serial.println("idDHT11 Example program");
  Serial.print("LIB version: ");
  Serial.println(IDDHT11LIB_VERSION);
  Serial.println("---------------");
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}
// This wrapper is in charge of calling
// mus be defined like this for the lib work
void dht11_wrapper() {
  DHT11.isrCallback();
}
void loop()
{
  Serial.print("\nRetrieving information from sensor: ");
  Serial.print("Read sensor: ");
  //delay(100);

  int result = DHT11.acquireAndWait();
  switch (result)
  {
  case IDDHTLIB_OK:
    Serial.println("OK");
    break;
  case IDDHTLIB_ERROR_CHECKSUM:
    Serial.println("Error\n\r\tChecksum error");
    break;
  case IDDHTLIB_ERROR_ISR_TIMEOUT:
    Serial.println("Error\n\r\tISR time out error");
    break;
  case IDDHTLIB_ERROR_RESPONSE_TIMEOUT:
    Serial.println("Error\n\r\tResponse time out error");
    break;
  case IDDHTLIB_ERROR_DATA_TIMEOUT:
    Serial.println("Error\n\r\tData time out error");
    break;
  case IDDHTLIB_ERROR_ACQUIRING:
    Serial.println("Error\n\r\tAcquiring");
    break;
  case IDDHTLIB_ERROR_DELTA:
    Serial.println("Error\n\r\tDelta time to small");
    break;
  case IDDHTLIB_ERROR_NOTSTARTED:
    Serial.println("Error\n\r\tNot started");
    break;
  default:
    Serial.println("Unknown error");
    break;
  }
  Serial.print("Humidity (%): ");
  Serial.println(DHT11.getHumidity(), 2);

  Serial.print("Temperature (oC): ");
  celtemp = DHT11.getCelsius();
  Serial.println(celtemp,2);

  for (int j=0 ; j<5; j++) {
    row = (_digits[(int) celtemp / 10].d[j] << 4) | _digits[(int) celtemp % 10].d[j];
    lc.setRow(0,j,row);
  }

  Serial.print("Temperature (oF): ");
  Serial.println(DHT11.getFahrenheit(), 2);

  Serial.print("Temperature (K): ");
  Serial.println(DHT11.getKelvin(), 2);

  Serial.print("Dew Point (oC): ");
  Serial.println(DHT11.getDewPoint());

  Serial.print("Dew Point Slow (oC): ");
  Serial.println(DHT11.getDewPointSlow());

  delay(2000);
}


