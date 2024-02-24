/*
EP2Mega
This sketch reads the contents of a 'parallel' programmable Read Only Memory ((E)(E)PROM)
Currently Supported IC's:
*AM27Cxxxx series EPROMs
*/

// Libraries
#include <SPI.h>
#include <SD.h>


unsigned long start;
// Config parametersAddress = 0;
unsigned long endAddress = 0x40000;

//Output file name (must be all lowercase?)
String fileName = "hp54601b.bin";

// IO pins
// Address pins {D2 - D19}
int addressPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };

// Data pins {22 - 37}
int dataPins[] = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37 };


// Define control pins
#define SD_CS 53     // SD card Chip Enable
#define EPROM_CE 21  //EPROM Chip Enable
#define EPROM_OE 20  //EPROM Output Enable


// File to save the binary data
File dataFile;

void setup() {
  Serial.begin(9600);

  // Initialize SD card
  if (!SD.begin(SD_CS)) {
    Serial.println("SD card initialization failed!");
    while (1)
      ;
  }
  Serial.println("Initialization done.");


  // Open a file to save the data
  dataFile = SD.open(fileName, FILE_WRITE);

  if (!dataFile) {
    Serial.println("Error opening file!");
    while (1)
      ;
  }

  //pinMode(PGM,OUTPUT);
  //digitalWrite(PGM,HIGH);

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
  for (int i = 0; i < (sizeof(addressPins) / 2); i++) //Set EPROM address pins LOW
    digitalWrite(addressPins[i], LOW);

  // Begin EPROM read
  Serial.println("Reading EPROM...");
  // Enable chip and output
  digitalWrite(EPROM_CE, LOW);
  digitalWrite(EPROM_OE, LOW);

  // Read and save data from the EPROM
  unsigned long address = startAddress;
  bool readFailed = false;

  while (address < endAddress) {

    // Set the address on EPROM
    setAddress(address);

    // Read data from EPROM and save it to the file
    uint16_t data = readData();

    //SD card library reads data from an 8-bit variable
    //Which is why we need to split the 16-bit data into upper and lower sections.
    uint8_t dataBytes[2];
    dataBytes[0] = (data >> 8) & 0xFF;  // Upper byte
    dataBytes[1] = data & 0xFF;         // Lower byte

    //Checks if any R/W errors occured (and stops writing if it did)
    if (dataFile.write(dataBytes, sizeof(dataBytes)) != sizeof(dataBytes)) {
      Serial.println("Error writing to file!");
      readFailed = true;
      break;
    }
    address++;
  }

  // Disable the chip and output
  digitalWrite(EPROM_CE, HIGH);
  digitalWrite(EPROM_OE, HIGH);

  // Close the file
  dataFile.close();


  if (readFailed) {
    Serial.println("Read failed!");
  } else {
    Serial.println("Read finished successfully!");
    Serial.println(address);
  }

}

void loop() {
  //nothing to do after finishing read.
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