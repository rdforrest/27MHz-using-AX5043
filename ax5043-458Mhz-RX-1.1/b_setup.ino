# include <SPI.h>

uint8_t slaveSelectPin = 10; // CS Chip Select
uint8_t MISOPin = 12; // MISO
uint16_t regAddr = 0x00;
uint16_t regVal = 0x00;
uint16_t configure1[2][12]; // Declare array
uint16_t configure2[2][13]; // Declare array
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

  // uint16_t configure1[2][10]  = { { 0xF10, 0xF11, 0xF35, 0x184, 0xF34, 0x032, 0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x02, 0x28, 0x04, 0x19, 0x9F, 0x72, 0xC0,  } }; // configuration values into array for 433 MHz
  // uint16_t configure1[2][10]  = { { 0xF10, 0xF11, 0xF35, 0x184, 0xF34, 0x032,0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x02, 0x28, 0x04, 0x19, 0xA0, 0xD8, 0xB8,  } }; // configuration values into array for 434 MHz
  // uint16_t configure1[2][10]  = { { 0xF10, 0xF11, 0xF35, 0x184, 0xF34, 0x032, 0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x02, 0x28, 0x04, 0x1B, 0x47, 0x33, 0x34,  } }; // configuration values into array for 436.45 MHz
  // uint16_t configure1[2][10]  = { { 0xF10, 0xF11, 0xF35, 0x184, 0xF34, 0x032,0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x02, 0x28, 0x04, 0x19, 0xB7, 0x85, 0x85,  } }; // configuration values into array for 435,50 MHz
  uint16_t configure1[2][10]  = { { 0xF10, 0xF11, 0xF35, 0x184, 0xF34, 0x032, 0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x02, 0x28, 0x04, 0x1C, 0xAC, 0x00, 0x00,  } }; // configuration values into array for 458.75 MHz

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

  // RX settings
  Serial.print("\n"); //newline
  Serial.print("Putting in RX settings.");
  Serial.print("\n"); //newline

  // RX settings. (Wire mode is set up by putting in 2 registers at the end - 0x22 and 0x23. Values 0x04, 0x04 respectively.)
  uint16_t configure2[2][22]  = { {0x10, 0x102, 0x126, 0x103, 0x104, 0x105, 0x100, 0x101, 0x109, 0x10A, 0x10B, 0x110, 0x111, 0x112, 0x113, 0x114, 0x121, 0x120, 0x124, 0x125, 0x12C, 0x12D }, {0x0A, 0x18, 0x03, 0x01, 0x15, 0xC8, 0x01, 0x55, 0x00, 0x0E, 0xBF, 0x00, 0xD9, 0x00, 0x76, 0x08, 0x89, 0xA7, 0x95, 0x91, 0x00, 0x00 } }; // configuration values into array

  // Putting in settings
  for (int i = 0; i < 22; i++)
  {
    for (int j = 0; j < 1; j++)
    {
      regAddr = configure2[j][i];
      regVal = configure2[j + 1][i];

      writeRegister(regAddr, regVal); // Function call
    }
  }
  Serial.print("\n"); //newline
  Serial.print("AX5043 configuration finished");
  Serial.print("\n"); //newline
  Serial.print("\n"); //newline

  regAddr = 0x02; // PWRMODE register
  regVal = 0x69;  // Receiver running
  writeRegister(regAddr, regVal); // Function call
  Serial.print("PWRMODE register(0x02) set to RX running");
  Serial.print("\n"); //newline
  Serial.print("\n"); //newline

  regAddr = 0x02; // PWRMODE register
  regVal = 0x65;  // Standby
  writeRegister(regAddr, regVal); // Function call

  regAddr = 0x02; // PWRMODE register
  regVal = 0x67;  // FIFO enabled
  writeRegister(regAddr, regVal); // Function call

  regAddr = 0x02; // PWRMODE register
  regVal = 0x69;  // RX running
  writeRegister(regAddr, regVal); // Function call

}
