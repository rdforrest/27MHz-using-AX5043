void loop() {

  regAddr = 0x02; // PWRMODE register
  regVal = 0x6D;  // Transmitter running
  writeRegister(regAddr, regVal); // Function call
  Serial.print("PWRMODE register(0x02) set to Transmitter running");
  Serial.print("\n"); //newline
  Serial.print("\n"); //newline

  delay(10000);                // waits for 10 second

  regAddr = 0x02; // PWRMODE register
  regVal = 0x65;  // Standby
  writeRegister(regAddr, regVal); // Function call

  regAddr = 0x02; // PWRMODE register
  regVal = 0x67;  // FIFO enabled
  writeRegister(regAddr, regVal); // Function call

  delay(2000);                // waits for 2 second

}
