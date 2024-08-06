#include "Arduino.h"
#include "OneButton.h"

//4-Digit Display:
#include "TM1637TinyDisplay.h"

#include "TM1637TinyDisplay6.h"       // Include 6-Digit Display Class Header


// Define Display:
#define CLK 2
#define DIO 3
// Create display object of type TM1637Display:
//TM1637TinyDisplay display(CLK, DIO);

TM1637TinyDisplay6 display(CLK, DIO); // 6-Digit Display Class

// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};

// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};


//Butto-Definitionen:
int BUTTON_PIN = A0;
OneButton NameTaster(BUTTON_PIN, true, true);

// Variablen der Zeit
float StartZeit;
float VerstricheneZeit;
float Sekunden;
bool Anzeige = false;
// TasterStatus sorgt für Start/Neustart
bool TasterStatus = true;

void setup() {
  //initieren Serieller Monitor:
  Serial.begin(9600);
  Serial.println("Programm gestartet!");

  
  // Aktionen dem Modus des Tasters zuordnen
  NameTaster.attachClick(einKlick);

  NameTaster.attachDoubleClick(doppelKlick);
  /*
  Anzahl der Millisekunden festlegen
  Standardwerte gesetzt:
  PressTicks: 1000
  ClickTicks: 600
  DebounceTicks: 50
  wenn die Standardwerte gesetzt werden sollen
  können die nächsten Zeilen auskommentiert werden
  */
  NameTaster.setPressTicks(1000);
  NameTaster.setClickTicks(500);
  NameTaster.setDebounceTicks(50);

  //Display initialisieren:
  display.clear();

  display.setSegments(data);
  display.setBrightness(15);
}


void loop() {
  
  NameTaster.tick();
  if(Anzeige){
    float Sekunden;
    Sekunden = zeitBerechnen();

    int IntSekunden  = int(Sekunden);

    // Minuten berechnen
    int Minute  = IntSekunden/ 60;
    if (Minute > 0){
      IntSekunden = IntSekunden + Minute*100;
    }

  // von Sekunden Anzahl der Minuten abziehen
  IntSekunden = IntSekunden - Minute * 60;
  float displayTime = IntSekunden/100;
  
  display.showNumberDec(IntSekunden,0b01000000 ,true,4);
  
  //printSerial(Sekunden);  
  } else { //Anzeige = false   
  //
  }
  display.setBrightness(15);
  
}

float zeitBerechnen(){
    float Sekunden;
    VerstricheneZeit = millis() - StartZeit;
    Sekunden = VerstricheneZeit / 1000;
        
    return Sekunden;
}


void einKlick()
{
  if (TasterStatus){
    StartZeit = millis();
    Anzeige = true;

    Serial.println("Timer start");
  } else {
    Anzeige = false;
  }

  // Tasterstatus umkehren
  TasterStatus = !TasterStatus;
}


void doppelKlick()
{
  Serial.println("00.00");
  display.showNumber(0);
  Anzeige=false;
}

void printSerial(float Sekunden)
{
  String GesamtSekunden = String(Sekunden);
    // . durch , ersetzen
    GesamtSekunden.replace(".", ",");
    // Ausgabe im Seriellen Monitor
    Serial.println("Sekunden insgesamt: " + GesamtSekunden + " Sekunden");

    // Minuten berechnen
    int Minute  = int(Sekunden) / 60;

    // nur Ausgabe der Minuten wenn Minute > 0
    if (Minute > 0){
      // Ausgabe verschönern, wenn Minute > 1 -> Ausgabe "Minuten"
      // "Minute"
      if (Minute > 1){
        // hier die ausgabe für Zeit über 1 Min
        
      } else {
        // hier die ausgabe für Zeit über 1 Min
        
      }
    }

    // von Sekunden Anzahl der Minuten abziehen
    Sekunden = Sekunden - Minute * 60;

    // Sekunden in String umwandeln
    // damit . durch , ersetzt werden kann
    String AnzahlSekunden = String(Sekunden);

    // . durch , ersetzen
    AnzahlSekunden.replace(".", ",");
  
}
