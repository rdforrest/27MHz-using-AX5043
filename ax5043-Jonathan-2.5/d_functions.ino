

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
