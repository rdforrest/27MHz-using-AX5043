

void writeRegister(uint16_t regAddr, uint16_t regVal) {
  // /*
  // WRITE TO REGISTER
  digitalWrite(10, LOW);            // Select set the SS pin to LOW
  // SPI.transfer(0x87);                // 8 bit - bit 7 is R(0)W(1) and then 7 address bits
  SPI.transfer(0x80 + regAddr);                // 8 bit - bit 7 is R(0)W(1) and then 7 address bits
  // SPI.transfer(5);                  // data value
  SPI.transfer(regVal);                  // data value
  digitalWrite(10, HIGH);            // Deselect set the SS pin HIGH
  // */

  // Read the register we have just written to
  digitalWrite(10, LOW);
  // SPI.transfer(regAddr & 0x7F);   // send address + r/w bit
  SPI.transfer(0x00 + regAddr);                // 8 bit - bit 7 is R(0)W(1) and then 7 address bits
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
/*
  // (NOT WORKING) Debug Fxtal signal set PINFUNCSYSCLK (x21) to output fxtal/16
    uint16_t configure1[2][6]  = { { 0xF10, 0xF11, 0xF35, 0x32, 0x184, 0x21 }, { 0x03, 0x07, 0x10, 0x00, 0x02, 0x08  } }; // Debug fxtal/16

    for (int i = 0; i < 6; i++)
    {
    for (int j = 0; j < 1; j++)
    {
      regAddr = configure1[j][i];
      regVal = configure1[j + 1][i];

      writeRegister(regAddr, regVal); // Function call
    }
    }

    Serial.print("\n"); //newline
    Serial.print("Debug Fxtal signal finished");
*/
