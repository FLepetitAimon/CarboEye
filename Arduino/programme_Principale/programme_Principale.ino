#include <Adafruit_ADS1X15.h>
#include <SPI.h>


// ------------------------------------------
// --------------  Constantes  --------------
// ------------------------------------------

#define Pin_Iref 0                // Pin d'entrée sur l'ADC du signal de référence 
#define Pin_Ifiltre 1             // Pin d'entrée sur l'ADC du signal issu du filtre exposé
#define T_ECHANTILLONAGE 60000    // Periode d'echantillonage
#define sigma 16.6                // coefficient d'attenuation de masse mg/m3
#define l_380 LOW                 // Tension de grille du transistor pour activé les LEDs - 380nm
#define l_880 HIGH                // Tension de grille du transistor pour activé les LEDs - 880nm
#define SwitchLambda 1            // Pin de sortie sur l'arduino de controle de la grille du transistor
#define Dfiltre 3.0              // diamètre du conduit contenant le filtre

const int freqOutputPin = 9;   // OC1A output pin for ATmega32u4 (Arduino Micro)
const int ocr1aval  = 7;
const int dataReady = 8;
const int CS = 10;
const int RESET = 7;




// ------------------------------------------
// --------------  Variables  ---------------
// ------------------------------------------

long AuxTime;                      // Variables Mémoire de la fonction millis()
float TabTest[2] = {1.1, 1.2};
float dATN[2] ;                   // Tableau de différence d'atténuation pendant une periode d'echantillonage pour chaque longueur d'onde: [dATN_380nm, dATN_880nm]
float Q = 0.000016;                          // Débit du flux d'air à travers le filtre
float newATN[2], oldATN[2];           // Tableau Mémoire des mesures de transmission: [***ATN_380nm, ***ATN_880nm]
float AverageBC[2];                 // Tableaud de la concentration moyenne de la dernière mesure: [BC_380nm, BC_880nm]

uint32_t measure;
uint8_t readfilterlow;
uint8_t readfilterhigh;
uint8_t readmode;
int8_t readtest;
bool bits24 = true; //24 bit from data register

Adafruit_ADS1115 ads;             // Objet pour manipuler l'ADC


// ------------------------------------------
// --------------  Fonctions  ---------------
// ------------------------------------------


uint8_t writeSmallReg( uint8_t ain, uint8_t reg, uint8_t value) { // only valid for 8 bit registers 0..4

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

uint8_t readByteRegister( uint8_t ain, uint8_t reg) { // only valid for 8 bit registers 0..4

  uint8_t result = 0;
  if (reg < 5) { // byte registers
    uint8_t cmd = 0; // a place to build the correct comm reg value.
    cmd = (reg << 4); // set the correct RS2..RS0 bits of COMM register
    cmd = cmd | ain; // keep the analog mux to channel 4.
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

uint32_t readbigRegister( uint8_t ain, uint8_t reg) { // only valid for 16,24 bit registers 5..7

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


//************************************************************************
// Initialisation de du capteur, à réaliser dans le setup() du programme *
//************************************************************************

void InitialiserCarbonEye() {
  // if (!ads.begin()) {
  //  Serial.println("Failed to initialize ADS.");
  //  while (1);
  //}
  pinMode(SwitchLambda, OUTPUT);
  digitalWrite(SwitchLambda, l_380);
}



//*************************************************************************************
// Renvoie un tableau contenant la mesure de transmission pour deux longueurs d'onde: *
// ATN[0]: lamnda=380nm   -  ATN[1]: lamnda=880nm                                     *
//*************************************************************************************
void ReadCurrentATN(float ATN[2]) {

  float Iref = 0;
  float Ifiltre = 0;

  digitalWrite(SwitchLambda, l_380);
  delay(50);

  for (int i = 0; i < 1; i++) {
    while (!(digitalRead(dataReady))); //wait for drdy to go low
    delay(500);
    Iref += (float(readbigRegister(0x00, 5)) / 16777216.0) * 5;
    while (!(digitalRead(dataReady))); //wait for drdy to go low
    delay(500);
    Ifiltre += (float(readbigRegister(0x01, 5)) / 16777216.0) * 5;

    Serial.println("Iref: " + String(Iref, 5) + " Ifiltre: " + String(Ifiltre, 5));
  }
  Iref = Iref ;
  Ifiltre = Ifiltre ;

  ATN[0] = 100 * log(Iref / Ifiltre);

  //digitalWrite (SwitchLambda, l_880);
  //delay(50);
  Iref = 0;
  Ifiltre = 0;
  for (int i = 0; i < 1; i++) {
    while (!(digitalRead(dataReady))); //wait for drdy to go low
    delay(500);
    Iref += (float(readbigRegister(0x00, 5)) / 16777216.0) * 5;
    while (!(digitalRead(dataReady))); //wait for drdy to go low
    delay(500);
    Ifiltre += (float(readbigRegister(0x01, 5)) / 16777216.0) * 5;
  }

  ATN[1] = 100 * log(Iref / Ifiltre);
}


//*************************************************************************
// Convertie la difference d'attenuation en concentration de Carbone Suie *
// Voir fiche technique pour plus d'info                                  *
//*************************************************************************
void ConcentrationBC(float d_ATN[2], float BC[2]) {

  float AirFiltre = PI * (Dfiltre * 0.001 / 2.0) * (Dfiltre * 0.001 / 2.0);
  AirFiltre = 0.00003;

  BC[0] = pow(10, 9) * AirFiltre * d_ATN[0] / (sigma  * Q * 100 * (T_ECHANTILLONAGE / 1000)) ;
  BC[1] = pow(10, 9) * AirFiltre * d_ATN[1] / (sigma * Q * 100 * (T_ECHANTILLONAGE / 1000)) ;

}


//*************************
// Affichage des mesures  *
//*************************
void AffichageMesure(float *Average_BC, float *d_ATN, float *new_ATN) {
  Serial.println("Mesure de Carbone suie au cours des dernires 60 secondes:");
  Serial.println("En utilisant les led 380nm \nBC = " + String(Average_BC[0], 5) + " ng/m3\ndATN = " + String(d_ATN[0], 5) + " %\nATN = " + String(new_ATN[0], 5) + " %");
  Serial.println("En utilisant les led 880nm \nBC = " + String(Average_BC[1], 5) + " ng/m3\ndATN = " + String(d_ATN[1], 5) + " %\nATN = " + String(new_ATN[1], 5) + " %");
  Serial.print("\n\n");
}




// --------------------------------------------------
// --------- *** Programme Principale *** -----------
// --------------------------------------------------


void setup() {

  // génére un siganl horloge de 1MHz
  pinMode(freqOutputPin, OUTPUT);
  TCCR1A = ( (1 << COM1A0));
  TCCR1B = ((1 << WGM12) | (1 << CS10));
  TIMSK1 = 0;
  OCR1A = ocr1aval;

  Serial.begin(9600);                                //initialisation du serial et du capteur
  InitialiserCarbonEye();

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
  uint8_t i = 0x01;
  writeSmallReg(i, 2, 0x44);   //Filter High, bipolar, 24-bit, current boost on, CLCKDIS 0
  writeSmallReg(i, 3, 0xA0);   //Filter Low Register FS11-FS0=0001 1000 0000 Filter first notch = 50Hz -3dB = 13.1Hz
  writeSmallReg(i, 1, 0x24);   //Self calibration
  while (!(digitalRead(dataReady) == 0)); //wait for calibration to finish
  Serial.println("Setup END");
  ///////////////////////Make sure Registers are Loaded with Correct Values/////////////////
  readfilterlow = readByteRegister (i, 3);
  readfilterhigh = readByteRegister (i, 2);
  readmode = readByteRegister (i, 1);
  readtest = readByteRegister (i, 4);
  Serial.print("Filter Low Register =  ");    //expected value= 0x80
  Serial.println(readfilterlow, HEX);
  Serial.print("Filter High Register =  ");   //expected value= 0x61
  Serial.println(readfilterhigh, HEX);
  Serial.print("Mode Register =  ");          //expected value= 0x0C
  Serial.println(readmode, HEX);
  Serial.print("Test Register =  ");          //expected value=???
  Serial.println(readtest, HEX);

  delay(2000);

  /////////////////////////////////////////////////////////////////////////////////////////

  i = 0x00;
  writeSmallReg(i, 2, 0x44);   //Filter High, bipolar, 24-bit, current boost on, CLCKDIS 0
  writeSmallReg(i, 3, 0xA0);   //Filter Low Register FS11-FS0=0001 1000 0000 Filter first notch = 50Hz -3dB = 13.1Hz
  writeSmallReg(i, 1, 0x24);   //Self calibration
  while (!(digitalRead(dataReady) == 0)); //wait for calibration to finish
  Serial.println("Setup END");
  ///////////////////////Make sure Registers are Loaded with Correct Values/////////////////
  readfilterlow = readByteRegister (i, 3);
  readfilterhigh = readByteRegister (i, 2);
  readmode = readByteRegister (i, 1);
  readtest = readByteRegister (i, 4);
  Serial.print("Filter Low Register =  ");    //expected value= 0x80
  Serial.println(readfilterlow, HEX);
  Serial.print("Filter High Register =  ");   //expected value= 0x61
  Serial.println(readfilterhigh, HEX);
  Serial.print("Mode Register =  ");          //expected value= 0x0C
  Serial.println(readmode, HEX);
  Serial.print("Test Register =  ");          //expected value=???
  Serial.println(readtest, HEX);
  //}
  /////////////////////////////////////////////////////////////////////////////////////////


  AuxTime = millis();                                //Mesure initiale de transmission
  ReadCurrentATN(newATN);





}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - AuxTime > 1000) {       // attente de la fin d'une periode d'echantillonage pour faire la mesure

    AuxTime = millis();                              // Mises à jour des variables
    oldATN[0] = newATN[0];
    oldATN[1] = newATN[1];

    ReadCurrentATN(newATN);                    // Mesure pour les deux longueurs d'onde
    dATN[0] = oldATN[0] - newATN[0];
    dATN[1] = oldATN[1] - newATN[1];
    ConcentrationBC(dATN, AverageBC);
    AffichageMesure(AverageBC, dATN, newATN);      // Affichage des mesures sur le ports series
  }


}
