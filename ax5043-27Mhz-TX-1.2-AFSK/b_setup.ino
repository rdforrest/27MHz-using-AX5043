# include <SPI.h>

uint8_t slaveSelectPin = 10; // CS Chip Select
uint8_t MISOPin = 12; // MISO
uint16_t regAddr = 0x00;
uint16_t regVal = 0x00;
uint16_t configure1[2][10]; // Declare array
uint16_t configure2[2][13]; // Declare array
uint16_t configure3[2][7]; // Declare array
uint16_t configure4[2][10]; // Declare array
int i = 0;
int j = 0;

void setup() {
  Serial.begin(9600);
  digitalWrite(slaveSelectPin, HIGH);
  pinMode(slaveSelectPin, OUTPUT); // set the SS pin as an output
  SPI.begin();         // initialize the SPI library
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  // Reset the AX5043, (SEL Pin 14)
  digitalWrite(slaveSelectPin, HIGH);
  delay (1); // 1mS delay
  digitalWrite(slaveSelectPin, LOW);

  if ( MISOPin = HIGH)      // test bit shown.
  {
    // Reset test
    Serial.print("\n"); //newline
    Serial.print("Reset chip done OK. MISO now high");
    Serial.print("\n"); //newline
  }
  else
  {
    Serial.print("\n"); //newline
    Serial.print("Reset chip failed. MISO still low");
    Serial.print("\n"); //newline
  }

  regAddr = 0x02; // PWRMODE register
  regVal = 0x80;  // Set the Reset pin
  writeRegister(regAddr, regVal); // Function call
  Serial.print("PWRMODE register(0x02) set to reset");
  Serial.print("\n"); //newline

  regAddr = 0x02; // PWRMODE register
  regVal = 0x00;  // Set the Reset pin
  writeRegister(regAddr, regVal); // Function call
  Serial.print("PWRMODE register(0x02) set to power down");
  Serial.print("\n"); //newline

  Serial.print("Change Registers as per the Not Black Magic website");
  Serial.print("\n"); //newline

  //uint16_t configure1[2][10]  = { { 0xF10, 0xF11, 0xF35, 0x184, 0xF34, 0x032, 0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x00, 0x28, 0x34, 0x01, 0xB1, 0x99, 0x9A,  } }; // configuration values into array for 27.1 MHz
  // uint16_t configure1[2][10]  = { { 0xF10, 0xF11, 0xF35, 0x184, 0xF34, 0x032, 0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x00, 0x28, 0x34, 0x01, 0xB3, 0x33, 0x33,  } }; // configuration values into array for 27.2 MHz
  // Odd thing that PLL does not lock below 27.3 MHz ??
  uint16_t configure1[2][10]  = { { 0xF10, 0xF11, 0xF35, 0x184, 0xF34, 0x032, 0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x00, 0x28, 0x34, 0x01, 0xB4, 0xCC, 0xCD,  } }; // configuration values into array for 27.3 MHz
  // uint16_t configure1[2][10]  = { { 0xF10, 0xF11, 0xF35, 0x184, 0xF34, 0x032, 0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x00, 0x28, 0x04, 0x1B, 0x47, 0x33, 0x34,  } }; // configuration values into array for 436.45 MHz
  // uint16_t configure1[2][10]  = { { 0xF10, 0xF11, 0xF35, 0x184, 0xF34, 0x032, 0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x00, 0x28, 0x04, 0x1C, 0xAC, 0x00, 0x00,  } }; // configuration values into array for 458.75 MHz
  // uint16_t configure1[2][10]  = { { 0xF10, 0xF11, 0xF35, 0x184, 0xF34, 0x032, 0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x00, 0x28, 0x04, 0x1C, 0xA0, 0x00, 0x00,  } }; // configuration values into array for 458.00 MHz
  Serial.print("Frequency set to 27.3 MHz");
  Serial.print("\n"); //newline

  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 1; j++)
    {
      regAddr = configure1[j][i];
      regVal = configure1[j + 1][i];

      writeRegister(regAddr, regVal); // Function call
    }
  }

  Serial.print("Initial Configuration finished");
  Serial.print("\n"); //newline

  delay(1000); // wait for 1 sec for auto ranging

  byte value = regVal ;      // test bit shown. Test if both are true.
  byte testbit4 = 0x10 ;     // a byte with only bit 4 set
  if ( value & testbit4 )      // test bit shown. Test if both are true.
    //  if (bitRead(regVal, 5) = HIGH ) // test bit shown. Test if both are true. Does not work.
  {
    // Auto ranging failed
    Serial.print("Auto ranging failed");
    Serial.print("\n"); //newline
  }
  else
  {
    // Auto ranging successful
    Serial.print("\n"); //newline
    Serial.print("Auto ranging successful");
    Serial.print("\n"); //newline
    Serial.print("\n"); //newline
  }
  // Read the register for the address below:
  regAddr = 0x33;
  // uint16_t regVal = 0x00;
  digitalWrite(10, LOW);
  // SPI.transfer(regAddr & 0x7F);   // send address + r/w bit
  SPI.transfer(0x00 + regAddr);      // 8 bit - bit 7 is R(0)W(1) and then 7 address bits
  regVal = SPI.transfer(0);          // retrieve reg value

  // display reg value
  Serial.print("regAddr: ");
  Serial.print(regAddr, HEX);
  Serial.print("   regVal H: ");
  Serial.print(regVal, HEX);
  Serial.print("   regVal B: ");
  Serial.println(regVal, BIN);
  digitalWrite(10, HIGH);

  // TX settings
  Serial.print("\n"); //newline
  Serial.print("Putting in TX settings.");
  Serial.print("\n"); //newline

  // TX settings. (Wire mode is set up by putting in 2 registers at the end - 0x22 and 0x23. Values 0x04, 0x04 respectively.)
  // Note that Afskmark and Afkspace registers (0x110, 0x111, 0x112, 0x113) are different for TX & RX  (TX values are 0x02, 0x05, 0x01, 0x04)
  uint16_t configure2[2][13]  = { {  0x010, 0x165, 0x166, 0x167, 0x161, 0x162, 0x163, 0x110, 0x111, 0x112, 0x113, 0x16A, 0x16B }, { 0x0A, 0x04, 0x0E, 0x0B, 0x0A, 0x08, 0x0E, 0x02, 0x05, 0x01, 0x04, 0x40, 0x96 } }; // configuration values into array

  // Putting in settings
  for (int i = 0; i < 13; i++)
  {
    for (int j = 0; j < 1; j++)
    {
      regAddr = configure2[j][i];
      regVal = configure2[j + 1][i];

      writeRegister(regAddr, regVal); // Function call
    }
  }

  // Encoding & Framing settings
  Serial.print("\n"); //newline
  Serial.print("Putting in Encoding & Framing settings.");
  Serial.print("\n"); //newline

  // Encoding & Framing settings.
  uint16_t configure3[2][7]  = { {  0x011, 0x012, 0xF72, 0x201, 0x203, 0x233, 0x230 }, { 0x03, 0x014, 0x00, 0xF0, 0xFF, 0x20, 0x0D } }; // configuration values into array

  // Putting in settings
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 1; j++)
    {
      regAddr = configure3[j][i];
      regVal = configure3[j + 1][i];

      writeRegister(regAddr, regVal); // Function call
    }
  }
  Serial.print("\n"); //newline
  Serial.print("AX5043 Encoding & Framing configuration finished");
  Serial.print("\n"); //newline
  Serial.print("\n"); //newline

  Serial.print("\n"); //newline
  Serial.print("AX5043 TX configuration finished");
  Serial.print("\n"); //newline
  Serial.print("\n"); //newline



}
