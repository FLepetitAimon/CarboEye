// Reads value from load cell but only goes between half and full output
/* Hardware Connections Arduino <--> AD7714
  PIN 1 -> SCLK : external clock SPI Arduino
  PIN 2 -> MCLK IN : 2.4576 MHz by crystal (input)
  PIN 3 -> MCLK OUT : 2.4576 MHz (output)
  PIN 4 -> POL = 0: first transition of the serial clock in a data transfer operation is from a low to a high
  PIN 5 -> (SYNC) = 1 : synchronization of the digital filters and analog modulators
  PIN 6 -> (RESET) : Reset (PIN 2) Arduino
  PIN 7/8/9/10 -> AIN1/AIN2/AIN3/AIN4 : Analog Input Channel
  PIN 11 -> (STANDBY) = 1 : disable Standby
  PIN 12 -> AVdd = 5 V
  PIN 13 -> BUFFER = 0 : analog input is shorted out
  PIN 14 -> REF IN(-) = should be 0
  PIN 15 -> REF IN(+) = Should be 3.8V
  PIN 16/17 -> AIN5/AIN6 : Analog Input Channel  no connect
  PIN 18 -> AGND = GND
  PIN 19 -> (CS) : chip select SPI (PIN 3) Arduino
  PIN 20 -> (DRDY) : (PIN 4) logic input of the AD7714
  PIN 21 -> DOUT : serial data output, MISO SPI Arduino
  PIN 22 -> DIN : serial data input, MOSI SPI Arduino
  PIN 23 -> DVdd = 5 V
  PIN 24 -> DGND = GND

 
void setup()
{
   pinMode(freqOutputPin, OUTPUT);
   
   TCCR1A = ( (1 << COM1A0));
  
   TCCR1B = ((1 << WGM12) | (1 << CS10));

   TIMSK1 = 0;
   
   OCR1A = ocr1aval;  

   pinMode(2, INPUT);

   pinMode(3, INPUT);  
}

void loop()
{

if (digitalRead(2) == HIGH){
OCR1A = 1;
}

else if (digitalRead(2) == HIGH){
OCR1A = 3;
}
  
}
*/

#include <SPI.h>

const int freqOutputPin = 9;   // OC1A output pin for ATmega32u4 (Arduino Micro)
const int ocr1aval  = 7; 

/*ADC -> UNO Definitions*/
const int dataReady = 8;
const int CS = 10;
const int RESET = 7;

//Define Functions for R/W Registers
uint8_t writeSmallReg( uint8_t reg, uint8_t value);
uint8_t readByteRegister( uint8_t reg);
uint32_t readbigRegister( uint8_t reg);

//8 or 32 Bit Integers
uint32_t measure;
uint8_t readfilterlow;
uint8_t readfilterhigh;
uint8_t readmode;
int8_t readtest;

bool bits24 = true; //24 bit from data register

void setup() {
  
  pinMode(freqOutputPin, OUTPUT);   
   TCCR1A = ( (1 << COM1A0));  
   TCCR1B = ((1 << WGM12) | (1 << CS10));
   TIMSK1 = 0;
   OCR1A = ocr1aval;  
   pinMode(2, INPUT);
   pinMode(3, INPUT);
   
  Serial.begin(9600);

  //SPI Setup
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(210);  // Slow down SPI clock
  SPI.setDataMode(SPI_MODE2);

  pinMode(dataReady, INPUT);
  pinMode(CS, OUTPUT);
  pinMode(RESET, OUTPUT);

  digitalWrite(CS, HIGH);  //deselect ADC

  digitalWrite(RESET, LOW); //Reset ADC
  delay(100);
  digitalWrite (RESET, HIGH);

  Serial.println("Begin ADC Register Setup");
  delay(100);
  //Channel 4 Operation as Load Cell connected to AIN1 and AIN2
  writeSmallReg(2, 0x61);   //Filter High, bipolar, 24-bit, current boost on, CLCKDIS 0
  writeSmallReg(3, 0x80);   //Filter Low Register FS11-FS0=0001 1000 0000 Filter first notch = 50Hz -3dB = 13.1Hz
  writeSmallReg(1, 0x2C);   //Self calibration
  Serial.println("Setup END");
  while (!(digitalRead(dataReady) == 0)); //wait for calibration to finish
  ///////////////////////Make sure Registers are Loaded with Correct Values/////////////////
  readfilterlow = readByteRegister (3);
  readfilterhigh = readByteRegister (2);
  readmode = readByteRegister (1);
  readtest = readByteRegister (4);
  Serial.print("Filter Low Register =  ");    //expected value= 0x80
  Serial.println(readfilterlow, HEX);
  Serial.print("Filter High Register =  ");   //expected value= 0x61
  Serial.println(readfilterhigh, HEX);
  Serial.print("Mode Register =  ");          //expected value= 0x0C
  Serial.println(readmode, HEX);
  Serial.print("Test Register =  ");          //expected value=???
  Serial.println(readtest, HEX);
  /////////////////////////////////////////////////////////////////////////////////////////

  // while (digitalRead(dataReady)==1);   //wait for drdy to go low
}
void loop  () {
  int val = 0;
  /*
    measure=readbigRegister(5);
    while (!(digitalRead(dataReady)));
    while (digitalRead(dataReady));
    while (!(digitalRead(dataReady)));
    while (digitalRead(dataReady));
    Serial.print(measure, HEX);
    Serial.println("=" + String((float(measure) / 16777216.0) * 3.9) + "V");
  */
  while (!(digitalRead(dataReady))); //wait for drdy to go low
  measure = readbigRegister(5);   //read data
  Serial.print(measure, HEX);
  Serial.println("=" + String((float(measure) / 16777216.0) * 3.863) + "V");   //ref voltage = 3.863V

}



uint8_t writeSmallReg( uint8_t reg, uint8_t value) { // only valid for 8 bit registers 0..4
  uint8_t ain = 0x04;
  uint8_t result = 0;
  if (reg < 5) { // byte registers
    uint8_t cmd = 0; // a place to build the correct comm reg value.

    cmd = (reg << 4); // set the correct RS2..RS0 bits of COMM register

    if (reg == 0) // update global ain Value
      ain = value & 7;

    cmd = cmd | ain; // keep the analog mux what it was previously configured as.

    digitalWrite(CS, LOW); // select the ADC

    uint8_t stat = SPI.transfer(cmd); // actually send the cmd and read the current status

    if (reg != 0) { // actually send the value to reg

      uint8_t unk = SPI.transfer(value);
      if (reg == 2) bits24 = (value & 0x40) == 0x40; // if configured for 24bit data register

    }
    digitalWrite(CS, HIGH); // all done with device
    result = stat; // return value received, drdy is bit 7.
  }
  return result;
}

uint8_t readByteRegister( uint8_t reg) { // only valid for 8 bit registers 0..4

  uint8_t result = 0;
  if (reg < 5) { // byte registers
    uint8_t cmd = 0; // a place to build the correct comm reg value.

    cmd = (reg << 4); // set the correct RS2..RS0 bits of COMM register

    cmd = cmd | 0x04; // keep the analog mux to channel 4.

    cmd = cmd | 0x08; // read mode

    digitalWrite(CS, LOW); // select the ADC

    result = SPI.transfer(cmd); // actually send the cmd and read the current status

    if (reg != 0) { // actually read the value of reg

      result = SPI.transfer(0); // 0 is just a place holder, the ADC ignores it. because of read mode
    }
    digitalWrite(CS, HIGH); // all done with device
  }
  return result;
}

uint32_t readbigRegister( uint8_t reg) { // only valid for 16,24 bit registers 5..7

  uint8_t ain = 0x04;
  uint32_t result = 0;
  if ((reg > 4) && (reg < 8)) { // big registers
    uint8_t cmd = 0; // a place to build the correct comm reg value.

    cmd = (reg << 4); // set the correct RS2..RS0 bits of COMM register

    cmd = cmd | ain; // keep the analog mux what it was previously configured as.

    cmd = cmd | 0x08; // read mode

    digitalWrite(CS, LOW); // select the ADC

    uint8_t stat = SPI.transfer(cmd); // actually send the cmd and read the current status
    uint8_t b = SPI.transfer(0); // send out placeholder get back byte
    result = b;
    b = SPI.transfer(0); // send out placeholder get back bigger byte
    result = (result << 8) + b; // build up 16 bit value from bytes
    if (bits24 || (reg > 5)) { //do a 24bit transfer
      b = SPI.transfer(0); // send out placeholder get back bigger byte
      result = (result << 8) + b; // build up 24 bit value from bytes.
    }
    digitalWrite(CS, HIGH); // all done with device
  }
  return result;
}
