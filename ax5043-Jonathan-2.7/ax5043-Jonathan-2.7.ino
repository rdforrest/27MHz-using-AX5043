

// ***********************************************************************************************
//  Name:      Basic read/write test
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

/*
   (Startup routine from Data sheet)
   Reset the Chip. Set SEL to high for at least 1μs, then low. Wait until MISO goes high.
  Set, and then clear, the RST bit of register PWRMODE.
  2. Set the PWRMODE register to POWERDOWN.
  3. Program parameters. It is recommended that suitable parameters are calculated
  using the AX_RadioLab tool available from Axsem.
*/
