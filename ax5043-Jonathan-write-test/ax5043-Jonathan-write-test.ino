

// ***********************************************************************************************
//  Name:      Basic write test
//  Date:       16 May 2022
//  Brief:       Crude SPI test - read write
//  Author:     Jonathan Askey
// ***********************************************************************************************

/* Hi David,

It's all a bit cryptic.

I have written to the registers....

Basically it wants two byte to be transferred via SPI to update a register value

BYTE ONE

8 bits - MSB is either 0 for read (00000000) or 1 for write (10000000)

We use the other 7 bits for the register address eg reg 7 being binary 0111

The end result for BYTE one is 10000111 or 87

BYTE two is simply the data value

I have run out of time - I will create a sketch with a bit mask that makes it easier


Regards
Jonathan
*/ 

 
/*  SPI connections
    Uno/Nano      AX5043
    MOSI  11      17
    MISO  12      16
    SCK   13      15
    SS    10      14
    3.3v          23
    GND            6
*/


#include <SPI.h>

uint8_t slaveSelectPin = 10; // CS Chip Select
uint8_t regAddr = 0x07;
uint8_t regVal=0;

void setup() {

  digitalWrite(slaveSelectPin, HIGH);
  pinMode(slaveSelectPin, OUTPUT); // set the SS pin as an output
  SPI.begin();         // initialize the SPI library
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));

  Serial.begin(9600);
  Serial.print("Register Write");
}

void loop() {

  // WRITE TO REGISTER
  digitalWrite(10, LOW);            // Select set the SS pin to LOW
  SPI.transfer(0x87);                // 8 bit - bit 7 is R(0)W(1) and then 7 address bits
  SPI.transfer(5);                  // data value 
  digitalWrite(10, HIGH);            // Deselect set the SS pin HIGH


  // Read the register we have just written to
  digitalWrite(10, LOW);
  SPI.transfer(regAddr & 0x7F);   // send address + r/w bit
  regVal = SPI.transfer(0);        // retrieve reg value

  // display reg value
  Serial.print("regAddr: ");
  Serial.print(regAddr, HEX);
  Serial.print("   regVal H: ");
  Serial.print(regVal, HEX);
  Serial.print("   regVal B: ");
  Serial.println(regVal, BIN);
  digitalWrite(10, HIGH);

}
