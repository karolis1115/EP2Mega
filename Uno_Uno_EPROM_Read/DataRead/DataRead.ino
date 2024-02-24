//A2EEP Data Read

// Pin Definitions
const int dataPins[] = { A0, A1, A2, A3, A4, A5, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };  // Connect to D0-D15 of EPROM
const int RX_READY = 2;                                                               // Digital pin for ready signal
const int TX_READY = 3;

volatile bool READY = false;


void setup() {
  Serial.begin(115200);

  for (int i = 0; i <= 15; i++) {
    pinMode(dataPins[i], INPUT);
  }

  pinMode(TX_READY, OUTPUT);
  pinMode(RX_READY, INPUT);


  // while (digitalRead(RX_READY) == HIGH) {
  //   Serial.println("Pulsing ready to AddressSet...");
  //   digitalWrite(TX_READY, LOW);
  //   delay(1000);
  // }
  // Serial.print("Comm Established");
  attachInterrupt(digitalPinToInterrupt(RX_READY), ReadyInt, RISING);
  digitalWrite(TX_READY, LOW);
}

void loop() {

  
  //while (READY == false) {}
  //READY = false;
  digitalWrite(TX_READY, LOW);
  delay(10);
  unsigned int data = readData();
  //process(data);
  digitalWrite(TX_READY, HIGH);

}





unsigned int readData() {
  unsigned int data = 0;
  for (int i = 0; i <= 15; i++) {
    //data |= digitalRead(dataPins[i]) << i;
    data = digitalRead(dataPins[i]);
    Serial.print(data);
  }
  Serial.println();
  return data;
}

void process(unsigned int data) {
  Serial.println(data);  // Print the received data (optional)
}


void ReadyInt(){
  READY = true;
}
