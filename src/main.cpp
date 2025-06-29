//! Pin configuration
//* I2C Pins
// SCL: xx
// SDA: xx
//* SPI Pins
// MOSI: xx
// MISO: xx
// SCK: xx
// SD card CS: xx
//* Analog Sensor Pins
// A0: xx
// A1: xx
// A2: xx
//* Digital Pins
// D2: xx
// D3: xx

// put function declarations here:
int myFunction(int, int);

void setup()
{
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}