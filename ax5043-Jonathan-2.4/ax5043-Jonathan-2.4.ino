

// ***********************************************************************************************
//  Name:      Basic write test
//  Date:       16 May 2022
//  Brief:       Crude SPI test - read write
//  Author:     Jonathan Askey
// ***********************************************************************************************

// RDF put in configuration values from : https://www.notblackmagic.com/bitsnpieces/ax5043/
// For 16 Mhz Crystal, RF 436.45 MHz. Power 12dBm

/*  SPI connections
    Uno/Nano      AX5043
    MOSI  11      17
    MISO  12      16
    SCK   13      15
    SS    10      14
    3.3v          23
    GND            6
*/


# include <SPI.h>

uint8_t slaveSelectPin = 10; // CS Chip Select
uint16_t regAddr = 0x00;
uint16_t regVal = 0x00;
uint16_t configure1[2][12]; // Declare array
uint16_t configure2[2][13]; // Declare array
int i = 0;
int j = 0;
