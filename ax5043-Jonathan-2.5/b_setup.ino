# include <SPI.h>

uint8_t slaveSelectPin = 10; // CS Chip Select
uint16_t regAddr = 0x00;
uint16_t regVal = 0x00;
uint16_t configure1[2][12]; // Declare array
uint16_t configure2[2][13]; // Declare array
int i = 0;
int j = 0;

void setup() {
  Serial.begin(9600);

  // Reset the AX5043, (SEL Pin 14)
  digitalWrite(slaveSelectPin, HIGH);
  delay (1);
  digitalWrite(slaveSelectPin, LOW);
  /*
    regAddr = 0x02; // PWRMODE register
    regVal = 0x13;  // Set the Reset pin
    writeRegister(regAddr, regVal); // Function call
    Serial.print("Chip reset");
    Serial.print("\n"); //newline
    Serial.print("\n"); //newline

    regAddr = 0x02; // PWRMODE register
    regVal = 0x00;  // Set the Reset pin
    writeRegister(regAddr, regVal); // Function call
    Serial.print("Chip set");
    Serial.print("\n"); //newline
    Serial.print("\n"); //newline
  */

  digitalWrite(slaveSelectPin, HIGH);
  pinMode(slaveSelectPin, OUTPUT); // set the SS pin as an output
  SPI.begin();         // initialize the SPI library
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));


  Serial.print("Change Registers as per Not Black Magic website");
  Serial.print("\n"); //newline
  Serial.print("\n"); //newline

  uint16_t configure1[2][11]  = { { 0xF10, 0xF11, 0xF35, 0x032, 0x021, 0xF34, 0x032, 0x34, 0x35, 0x36, 0x37, }, { 0x03, 0x07, 0x10, 0x00, 0x04, 0x28, 0x04, 0x1B, 0x47, 0x33, 0x34,  } }; // configuration values into array

  for (int i = 0; i < 11; i++)
  {
    for (int j = 0; j < 1; j++)
    {
      regAddr = configure1[j][i];
      regVal = configure1[j + 1][i];

      writeRegister(regAddr, regVal); // Function call

    }
  }
  Serial.print("\n"); //newline
  Serial.print("Initial Configuration finished");
  Serial.print("\n"); //newline


  // Initiate and check for successful auto ranging. Set  bit 4 of Ox33
  Serial.print("\n"); //newline
  Serial.print("Auto ranging started");
  Serial.print("\n"); //newline
  Serial.print("\n"); //newline
  uint16_t regAddr = 0x33;
  uint16_t regVal = 0x10;
  writeRegister(regAddr, regVal); // Function call

  delay(5000); // wait for 5 secs for auto ranging



  //byte value = 0x4 ;      // test bit shown. Test if both are true.
  if ( regVal & 0x10 )      // test bit shown. Test if both are true.
  {
    // Auto ranging failed
    Serial.print("\n"); //newline
    Serial.print("Auto ranging failed");
    Serial.print("\n"); //newline
    Serial.print("\n"); //newline
  }
  else
  {
    // Auto ranging successful
    Serial.print("\n"); //newline
    Serial.print("Auto ranging successful");
    Serial.print("\n"); //newline
    Serial.print("\n"); //newline

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

  }

  uint16_t configure2[2][13]  = { {  0x010, 0x165, 0x166, 0x167, 0x161, 0x162, 0x163, 0x110, 0x111, 0x112, 0x113, 0x16A, 0x16B }, { 0x0A, 0x04, 0x0E, 0x0B, 0xA, 0x8, 0xE, 0x02, 0x05, 0x01, 0x04, 0x30, 0x71} }; // configuration values into array


  // Carry out final configuration
  for (int i = 0; i < 13; i++)
  {
    for (int j = 0; j < 1; j++)
    {
      regAddr = configure2[j][i];
      regVal = configure2[j + 1][i];

      writeRegister(regAddr, regVal); // Function call

    }
  }
  Serial.print("\n"); //newline
  Serial.print("Final Configuration finished");
  Serial.print("\n"); //newline
}
