void loop() {

  regAddr = 0x02; // PWRMODE register
  regVal = 0x65;  // Standby
  writeRegister(regAddr, regVal); // Function call
  Serial.print("Standby");
  Serial.print("\n"); //newline

  regAddr = 0x02; // PWRMODE register
  regVal = 0x67;  // FIFO enabled
  writeRegister(regAddr, regVal); // Function call
  Serial.print("Fifo enabled");
  Serial.print("\n"); //newline

  delay(6000);                // waits for 6 second

  // TX switches on for 10 secs / Off for  6 secs.
  regAddr = 0x02; // PWRMODE register
  regVal = 0x6D;  // Transmitter running
  writeRegister(regAddr, regVal); // Function call
  Serial.print("Transmit on");
  Serial.print("\n"); //newline
  Serial.print("\n"); //newline

  // Send Packet
  uint16_t configure4[2][10]  = { {0x28, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x28} , { 0x03, 0x62, 0x18, 0x14, 0x55, 0xE1, 0x19, 0x03, 0xAA, 0x04 } }; // configuration values into array

  // Putting in settings
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 1; j++)
    {
      regAddr = configure4[j][i];
      regVal = configure4[j + 1][i];

      writeRegister(regAddr, regVal); // Function call
      Serial.print("Sending packet");
      Serial.print("\n"); //newline
    }
  }

  delay(10000);                // waits for 10 second




}
