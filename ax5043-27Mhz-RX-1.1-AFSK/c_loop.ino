void loop() {
  regAddr = 0x02; // PWRMODE register
  regVal = 0x65;  // Standby
  writeRegister(regAddr, regVal); // Function call

  regAddr = 0x02; // PWRMODE register
  regVal = 0x67;  // FIFO enabled
  writeRegister(regAddr, regVal); // Function call

  delay(4000);                // waits for 4 second

  regAddr = 0x02; // PWRMODE register
  regVal = 0x69;  // Receive mode
  writeRegister(regAddr, regVal); // Function call

  regAddr = 0x2A; // FIFOCOUNT register
  regVal = 0x00;  // Dummy value
  writeRegister(regAddr, regVal); // Function call
  Serial.print("Checking for Packet (FIFOCOUNT,)0x2A");
  Serial.print("\n"); //newline
  Serial.print("\n"); //newline

  delay(6000);                // waits for 10 second

}
