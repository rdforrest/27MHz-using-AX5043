# include <SPI.h>

uint8_t slaveSelectPin = 10; // CS Chip Select
uint8_t MISOPin = 12; // MISO
uint16_t regAddr = 0x00;
uint16_t regVal = 0x00;
uint16_t configure1[2][6]; // Declare array

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
  regVal = 0x05;  // XTAL oscillator enabled
  writeRegister(regAddr, regVal); // Function call
  Serial.print("PWRMODE register(0x02) set to XTAL oscillator enabled");
  Serial.print("\n"); //newline

  regAddr = 0x02; // PWRMODE register
  regVal = 0x05;  // XTAL oscillator enabled
  writeRegister(regAddr, regVal); // Function call
  Serial.print("PWRMODE register(0x02) set to XTAL oscillator enabled");
  Serial.print("\n"); //newline

  Serial.print("Change Registers as per the Not Black Magic website");
  Serial.print("\n"); //newline

  // Sysclk output (Pfsysclk) set to divide by 16
  uint16_t configure1[2][6]  = { { 0xF10, 0xF11, 0xF35, 0x032, 0x184, 0x21  }, { 0x03, 0x07, 0x10,  0x00, 0x00, 0x08,} }; // configuration values into array for 458.75 MHz

  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 1; j++)
    {
      regAddr = configure1[j][i];
      regVal = configure1[j + 1][i];

      writeRegister(regAddr, regVal); // Function call
    }
  }

  Serial.print("XTAL check finished (Freq divided by 16)");
  Serial.print("\n"); //newline

}
