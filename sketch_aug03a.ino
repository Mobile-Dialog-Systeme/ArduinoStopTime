#include "Arduino.h"
#include "U8g2lib.h"
#include "OneButton.h"
#include "SevSeg.h" //Die vorher hinzugefügte Library laden
SevSeg sevseg; //Ein sieben Segment Objekt initialisieren



int BUTTON_PIN = A0;

// Name des Tasters
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

  //Initieren 7-Segment Anzeige
  byte numDigits = 4; //Hier wird die Anzahl der Ziffern angegeben
  byte digitPins[] = {2, 3, 4, 5}; //Die Pins zu den Ziffern werden festgelegt
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; //Die Pins zu den //Segmenten werden festgelegt
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, false, false, true,false); //In diesem
  //Abschnitt kann man nun entweder testen welche Art von Display man besitzt oder
  //wenn man es schon weiß angeben ob es sich um ein COMMON_CATHODE oder
  //COMMON_ANODE Display handelt. Das Display funktioniert nur wenn die richtige
  //Art eingetragen ist, ansonsten werden alle Segmente gleichzeitig leuchten.

  sevseg.setNumber(0,4);
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
    
  sevseg.setNumber(IntSekunden,2); //Hier können wir nun die gewünschte Zahl eintragen.
  //Wir haben als Beispiel 1234 angegeben. Die Zahl hinter dem Komma steht für den
  //Punkt hinter einer Ziffer. Hierbei ist 3 der Punkt neben der ersten Ziffer und
  //0 wäre der Punkt ganz rechts neben der letzten Ziffer. Wenn man keinen Punkt
  //mit angezeigt haben möcht kann man z.B. 4 angeben.

  //printSerial(Sekunden);  
  } else {
    //sevseg.setNumber(0,4);
    //sevseg.setNumber(0,0);  
  }
  sevseg.refreshDisplay(); // Dieser Teil lässt die Nummer auf dem Display
  //erscheinen.
  
  sevseg.setBrightness(90); //Hier kann die Helligkeit des Displays angepasst
  //werden. In einem Bereich von 0-100 wobei 100 das Hellste ist. 0 bedeutet
  //jedoch nicht dass das Display komplett dunkel ist. Für die Anzeige einer Zahl
  //ist allein die "sevseg.refreshDisplay();" Zeile verantwortlich
}

float zeitBerechnen(){
  // Zeit berechnen
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
    //Sekunden = zeitBerechnen();
    //printSerial(Sekunden); 
    //Serial.println("Timer ende");
    Anzeige = false;
  }

  // Tasterstatus umkehren
  TasterStatus = !TasterStatus;
}


void doppelKlick()
{
  Serial.println("00.00");
  sevseg.setNumber(0,4);
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
