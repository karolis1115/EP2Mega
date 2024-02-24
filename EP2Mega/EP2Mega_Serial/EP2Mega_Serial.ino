/*
EP2Mega
This sketch reads the contents of a 'parallel' programmable Read Only Memory ((E)(E)PROM)
Currently Supported IC's:
*AM27Cxxxx series EPROMs
*/


/*
**Address pins** 
{A14-A17} -> {16 17 18 19}
{A7-A13} -> {23 25 27 29 31 33 35}
{A0-A6} -> {22 24 26 28 30 32 34}
*/

/*
**Data pins**
{D8-D15} -> {39 41 43 45 47 49 51 53}
{D0-D7} -> {38 40 42 44 46 48 50 52}
*/

//Chip control pins
//CE - 37
//OE - 36
//VPP (Programming Voltage) - External header

unsigned long startAddress = 0;

//unsigned long endAddress = 0x40000; //4096 kB
//unsigned long endAddress = 0x10000; //1024 kB
unsigned long endAddress = 0x10000;  //1024 kB



// IO pins
// Define control pins
#define EPROM_CE 37  //EPROM Chip Enable
#define EPROM_OE 36  //EPROM Output Enable


// Address pins {A0 - A17}
int addressPins[] = { 22, 24, 26, 28, 30, 32, 34, 23, 25, 27, 29, 31, 33, 35, 16, 17, 18, 19 };

// Data pins {D0 - D15}
int dataPins[] = { 38, 40, 42, 44, 46, 48, 50, 52, 39, 41, 43, 45, 47, 49, 51, 53 };


void setup() {
  Serial.begin(115200);

  // Wait for start signal from Python script
  /* Serial.println("Waiting for start signal...");
  while (endAddress == 0x00000) {
    endAddress = serialStopAddrress();
  }*/

  Serial.println("Waiting for start signal...");
  while (!waitForSignal()) {
    //wait
  }

  for (int i = 0; i < (sizeof(addressPins) / 2); i++)
    pinMode(addressPins[i], OUTPUT);

  for (int i = 0; i < (sizeof(dataPins) / 2); i++)
    pinMode(dataPins[i], INPUT);


  // Set EPROM pins as outputs
  pinMode(EPROM_CE, OUTPUT);
  pinMode(EPROM_OE, OUTPUT);


  // Set start state of EPROM
  digitalWrite(EPROM_CE, HIGH);  // Disable the chip
  digitalWrite(EPROM_OE, HIGH);  // Disable the output


  for (int i = 0; i < (sizeof(addressPins) / 2); i++)  //Set EPROM address pins LOW
    digitalWrite(addressPins[i], LOW);


  // Enable chip and output
  digitalWrite(EPROM_CE, LOW);
  digitalWrite(EPROM_OE, LOW);

  // Read and send data from the EPROM through Serial
  unsigned long address = startAddress;

  while (address < endAddress) {
    setAddress(address);  // Set the address on EPROM

    // Read data from EPROM and send it through Serial
    uint16_t data = readData();
    Serial.write((data >> 8) & 0xFF);  // Send high byte
    Serial.write(data & 0xFF);         // Send low byte

    address++;
  }


  // Disable the chip and output
  digitalWrite(EPROM_CE, HIGH);
  digitalWrite(EPROM_OE, HIGH);

  // Send stop signal to Python script
  Serial.write('**END**');
}

void loop() {
  //nothing to do after finishing read.
}


// unsigned long serialStopAddrress() {
//   while (!Serial.available()) {
//   }
//   unsigned long signal = Serial.read();
//   return signal;  // Expecting 'S' for start signal
// }

bool waitForSignal() {
  while (!Serial.available()) {}
  char signal = Serial.read();
  return (signal == 'S');  // Expecting 'S' for start signal
}

// Helper function to set the address on EPROM address pins
void setAddress(unsigned long address) {
  for (int i = 0; i < (sizeof(addressPins) / 2); i++) {
    digitalWrite(addressPins[i], (address & (1UL << i)) ? HIGH : LOW);
  }
}


// Helper function to read data from EPROM
uint16_t readData() {
  uint16_t data = 0;
  for (int i = 0; i < (sizeof(dataPins) / 2); i++) {
    data |= (digitalRead(dataPins[i]) << i);
  }
  return data;
}