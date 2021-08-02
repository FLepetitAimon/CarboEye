#include <SPI.h> 
 
// SS 10 // CS 
// MOSI 11 // DIN 
// MISO 12 // DOUT 
// SCK 13 // SCLK 
// RESET 7 
// DRDY 8 
 
// POL, AVdd, DVdd , SYNC, STANDBY = VCC 
// AGDN, DGDN, REF IN (-), BUFFER = GND 
// REF IN (+) = +1.25 ... 2.5 V 
#define RESET 7 
#define DRDY 8

  
long bt24, hi, mid , lo;
int in = 0b000;  // // Pseudo Differential // AIN1_AIN6 = 0b000 // AIN2_AIN6 = 0b001 // AIN3_AIN6 = 0b010 // AIN4_AIN6 = 0b011 // Fully Differential // AIN1_AIN2 = 0b100 // AIN3_AIN4 = 0b101 // AIN5_AIN6 = 0b110 void
 
const int freqOutputPin = 9;   // OC1A output pin for ATmega32u4 (Arduino Micro)
const int ocr1aval  = 7; 




 




 
void setup () { 
  pinMode(freqOutputPin, OUTPUT);   
   TCCR1A = ( (1 << COM1A0));  
   TCCR1B = ((1 << WGM12) | (1 << CS10));
   TIMSK1 = 0;
   OCR1A = ocr1aval;  
   pinMode(2, INPUT);
   pinMode(3, INPUT);
   
  Serial.begin(9600) ; 
  pinMode(DRDY, INPUT) ; // DRDY 
  pinMode(RESET, OUTPUT) ; // RESET 
  digitalWrite(RESET, LOW) ; 
  SPI.beginTransaction (SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE3)) ; 
  SPI.begin() ; 
  digitalWrite(RESET, HIGH) ; 
  delay(300) ;
  Serial.println("Initialisation DONE");
  } 
 
void loop () { 
  Write () ; 
  Serial.println("Write DONE");
  Read () ; 
  Serial.println("Read DONE");
  Serial.println (bt24) ;
  }  
 
void Write () { 
  digitalWrite (RESET, HIGH) ; 
  digitalWrite (SS, LOW) ; 
  delayMicroseconds (1) ;
/////////////// Filter High Register ////////////////////////////// /////////////
  // BU WL BST CLKDIS FS11 FS10 FS9 FS8 
  // BU 1 UNIPOLAR, 0 BIPOLAR 
  // WS 0 = 16 bit, 1 = 24 bit 
  // BST 2.4576 MHz BST = 0, 1.0000 MHz BST = 1 
  // CLKDIS 0 (from quartz) 
  // FSx HIGH 4 BITS FILTER (12 BITS) 
  SPI.transfer(0b00100000+in) ; // Communications Register> Filter High Register 
  SPI.transfer(0b11100001) ; // Filter High Register 
 
////////////// Filter Low Register //////////////////////////// ////////////////// 
  // FS7 FS6 FS5 FS4 FS3 FS2 FS1 FS0 
  // LOW 8 BITS FILTER (12 BITS) 
  SPI.transfer(0b00110000+in) ; // Communications Register> Filter Low Register 
  SPI.transfer(0b10000000) ; // Filter Low Register 
  // 2.4576 MHz / 128/4000 (111110100000) = 4.8 Hz 
  // FS11 ... FS8 1111, FS7 ... FS0 10100000 
 
//////////////// Mode Register ////////////////////////////////////////////// / 
  // MD2 MD1 MD0 G2 G1 G0 BO FSYNC 
  // MDx Operating Mode 
 
  // Gx Gain Setting 000 ... 111 = 1 ... 128 GAIN 
  // 000 = x1, 001 = x2, 010 = x4, 011 = x8 , 100 = x16, 101 = x32, 110 = x64, 111 = x128 
 
  // BO, FSYNC = 0 
  SPI.transfer (0b00010000+in) ; // Communications Register> Mode Register 
  SPI.transfer (0b00100000) ; // Mode Register // MDx = 001 Self-Calibration
  
  digitalWrite(SS, HIGH) ; 
  delay(10) ;
  }    
void Read ( ) { 
  while (digitalRead(DRDY) != LOW) ; 
         digitalWrite(SS, LOW) ; 
         delayMicroseconds(1); 
         SPI. transfer(0b01011000 + in) ;    
         hi = SPI.transfer(0xFF) ; 
         hi = hi << 16 ; 
         mid = SPI.transfer(0xFF) ; 
         mid = mid << 8 ; 
         lo = SPI.transfer(0xFF) ; 
         bt24 = hi | mid | lo; 
         digitalWrite(SS, HIGH) ;
         while(digitalRead (DRDY) != HIGH) ; 
         delay(10) ; 
         digitalWrite(RESET, LOW) ;
  }
