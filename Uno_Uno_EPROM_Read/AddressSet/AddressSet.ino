//A2EEP Address set

// Pin Definitions
const int addressPins[] = { A0, A1, A2, A3, A4, A5, 4, 5, 6, 7, 8, 9, 10, 12, 13, 9 };  // Connect to A0-A15 of EPROM
const int RX_READY = 2;                                                              // Connect to handshakeRX pin of Arduino 2
const int TX_READY = 3;                                                              // Connect to TX_READY pin of Arduino 2

// Setup Function
void setup() {

  Serial.begin(115200);
  // Configure address pins as outputs
  for (int i = 0; i <= 15; i++) {
    pinMode(addressPins[i], OUTPUT);
  }

  // Configure handshake pin as input
  pinMode(TX_READY, OUTPUT);
  pinMode(RX_READY, INPUT_PULLUP);




  // while (digitalRead(RX_READY) == HIGH) {
  //   Serial.println("Pulsing ready to DataSet...");
  //   digitalWrite(TX_READY, LOW);
  //   delay(1000);
  // }
  // Serial.println("Comm Established");
  digitalWrite(TX_READY, HIGH);

  attachInterrupt(digitalPinToInterrupt(RX_READY), arduino2ReadyInterrupt, LOW);
}

void loop() {
  //nothing in loop everything's gonna be taken care of in the interrupts
}




// Function to set address on EPROM
void setAddress(unsigned int address) {
  for (int i = 0; i <= 15; i++) {
    digitalWrite(addressPins[i], bitRead(address, i));
  }
}

// Interrupt Service Routine for handshake pin
void arduino2ReadyInterrupt() {
  for (int address = 0; address <= 65535; address++) {
    digitalWrite(TX_READY, HIGH);
    setAddress(address);
    Serial.print("Current address: ");
    Serial.println(address);

    digitalWrite(TX_READY, LOW);
  }
}
