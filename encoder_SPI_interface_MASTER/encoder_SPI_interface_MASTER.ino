// inslude the SPI library:
#include <SPI.h>

// set pin 10 as the slave select (Arduino Nano):
const int slaveSelectPin = 10;
int sampleData = -30000;
uint8_t MSB, LSB;
// initialse Arduino-friendly settings (this *MUST* be the same for the Slave)
SPISettings settingsA(8000000, MSBFIRST, SPI_MODE3);    //Run the SPI at 8MHz in MODE 3 with MSB sent first

void setup() {
  // set the slaveSelectPin as an output:
  pinMode(slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, LOW);
  // initialize SPI:
  SPI.begin();

  LSB = lowByte(sampleData);    //Data can only be sent as bytes - this splits the signed int (16bits) into
  MSB = highByte(sampleData);   //two bytes, ready for sending.  These variables are created as uint8_t.
}

void loop() {
  delay(100);
  SPI.beginTransaction(settingsA);
  SPI.transfer(MSB);
  SPI.transfer(LSB);
  SPI.transfer(sampleData);
  SPI.endTransaction();
}
