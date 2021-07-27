#include <Adafruit_ADS1X15.h>

// ------------------------------------------
// --------------  Constantes  --------------
// ------------------------------------------

#define Pin_Iref 0                // Pin d'entrée sur l'ADC du signal de référence 
#define Pin_Ifiltre 1             // Pin d'entrée sur l'ADC du signal issu du filtre exposé
#define T_ECHANTILLONAGE 10000    // Periode d'echantillonage
#define sigma 16.6                // coefficient d'attenuation de masse mg/m3
#define l_380 LOW                 // Tension de grille du transistor pour activé les LEDs - 380nm
#define l_880 HIGH                // Tension de grille du transistor pour activé les LEDs - 880nm
#define SwitchLambda 1            // Pin de sortie sur l'arduino de controle de la grille du transistor
#define Dfiltre 3.0              // diamètre du conduit contenant le filtre



// ------------------------------------------
// --------------  Variables  ---------------
// ------------------------------------------

long AuxTime;                      // Variables Mémoire de la fonction millis()
float TabTest[2] = {1.1, 1.2};
float dATN[2] ;                   // Tableau de différence d'atténuation pendant une periode d'echantillonage pour chaque longueur d'onde: [dATN_380nm, dATN_880nm]
float Q = 0.000016;                          // Débit du flux d'air à travers le filtre
float newATN[2], oldATN[2];           // Tableau Mémoire des mesures de transmission: [***ATN_380nm, ***ATN_880nm]
float AverageBC[2];                 // Tableaud de la concentration moyenne de la dernière mesure: [BC_380nm, BC_880nm]

Adafruit_ADS1115 ads;             // Objet pour manipuler l'ADC


// ------------------------------------------
// --------------  Fonctions  ---------------
// ------------------------------------------


//************************************************************************
// Initialisation de du capteur, à réaliser dans le setup() du programme *
//************************************************************************
void InitialiserCarbonEye() {
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
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
    Iref += ads.computeVolts(ads.readADC_SingleEnded(Pin_Iref));
    Ifiltre += ads.computeVolts(ads.readADC_SingleEnded(Pin_Ifiltre));
  }
  Iref = Iref ;
  Ifiltre = Ifiltre ;

  ATN[0] = 100 * log(Iref / Ifiltre);

  //digitalWrite (SwitchLambda, l_880);
  //delay(50);
  Iref=0;
  Ifiltre=0;
  for (int i = 0; i < 80; i++) {
    Iref += ads.computeVolts(ads.readADC_SingleEnded(Pin_Iref));
    Ifiltre += ads.computeVolts(ads.readADC_SingleEnded(Pin_Ifiltre));
  }
  Iref = Iref / 80;
  Ifiltre = Ifiltre / 80;

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
  Serial.println("En utilisant les led 380nm \nBC = " + String(Average_BC[0]) + " ng/m3\ndATN = " + String(d_ATN[0]) + " %\nATN = " + String(new_ATN[0]) + " %");
  Serial.println("En utilisant les led 880nm \nBC = " + String(Average_BC[1]) + " ng/m3\ndATN = " + String(d_ATN[1]) + " %\nATN = " + String(new_ATN[1]) + " %");
  Serial.print("\n\n");
}




// --------------------------------------------------
// --------- *** Programme Principale *** -----------
// --------------------------------------------------


void setup() {

  Serial.begin(9600);                                //initialisation du serial et du capteur
  InitialiserCarbonEye();

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
