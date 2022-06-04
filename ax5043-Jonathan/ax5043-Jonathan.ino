
// ***********************************************************************************************
//  Name:       SPI_readRegs_003
//  Date:       10 May 2022
//  Brief:      Crude SPI test - read write
//  Author:     Jonathan Askey
// ***********************************************************************************************

/*  SPI connections 
 *  Uno/Nano      AX5043
 *  MOSI  11      17
 *  MISO  12      16
 *  SCK   13      15
 *  SS    10      14
 *  3.3v          23
 *  GND            6
 */


#include <SPI.h>

uint8_t slaveSelectPin=10; // CS Chip Select

uint8_t regAddr;
uint8_t regVal;


void setup() {
 
  digitalWrite(slaveSelectPin, HIGH);
  pinMode(slaveSelectPin, OUTPUT); // set the SS pin as an output
  SPI.begin();         // initialize the SPI library
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  
  Serial.begin(9600);

  digitalWrite(10, HIGH);           // set the SS pin HIGH

}

void loop() {

  digitalWrite(10, LOW);            // set the SS pin to LOW
   
for (uint8_t regAddr = 0x021; regAddr <= 0x32; regAddr++)
  {
   
    SPI.transfer(regAddr & 0x7F); // send address + r/w bit
    regVal = SPI.transfer(0);
    

    Serial.print(regAddr, HEX);
    Serial.print(" - ");
    Serial.print(regVal,HEX);
    Serial.print(" - ");
    Serial.println(regVal,BIN);
  }

  digitalWrite(10, HIGH);           // set the SS pin HIGH
 }
