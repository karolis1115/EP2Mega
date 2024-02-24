//A2EEP Address set

// Pin Definitions
const int addressPins[] = { A0, A1, A2, A3, A4, A5, 4, 5, 6, 7, 8, 9, 10, 12, 13, 9, 0, 3};  // Connect to A0-A16 of EPROM
const int RX_READY = 2;                                                                    // Connect to handshakeRX pin of Arduino 2
//const int TX_READY = 3;

volatile bool READY = false;


long address = 0;  // Connect to TX_READY pin of Arduino 2

// Setup Function
void setup() {

  Serial.begin(115200);

  // Configure address pins as outputs
  for (int i = 0; i <= 17; i++) {
    pinMode(addressPins[i], OUTPUT);
  }

  // Configure handshake pin as input
  //pinMode(TX_READY, OUTPUT);
  pinMode(RX_READY, INPUT);

  // while (digitalRead(RX_READY) == HIGH) {
  //   Serial.println("Pulsing ready to DataSet...");
  //   digitalWrite(TX_READY, LOW);
  //   delay(1000);
  // }
  // Serial.println("Comm Established");
  //digitalWrite(TX_READY, HIGH);
  attachInterrupt(digitalPinToInterrupt(RX_READY), ReadyInt, RISING);

  //digitalWrite(TX_READY, HIGH);
  //setAddress(262141);
}

void loop() {

  


  while (READY == false) {}
  READY = false;
  //digitalWrite(TX_READY, LOW);

  setAddress(address);
  Serial.print("Current address: ");
  Serial.println(address);
  address++;
  
  //digitalWrite(TX_READY, HIGH);*/
}




// Function to set address on EPROM
void setAddress(unsigned int address) {
  for (int i = 0; i <= 17; i++) {
    digitalWrite(addressPins[i], bitRead(address, i));
  }
}



void ReadyInt(){
  READY = true;
}
