#ifndef IO_h
#define IO_h

#include "config.h"

class IO
{
public:
  IO();

  // Analoge Sensoren
  Pin temperaturePcb      = Pin(  A13,    INPUT,         ANALOG   );  // misst Temperatur nahe den Motortreibern
  Pin brightnessPcb       = Pin(  A10,    INPUT_PULLUP,  ANALOG   );  // misst Helligkeit rechts auf der Platine
  Pin batteryVoltage      = Pin(  A11,    INPUT,         ANALOG   );  // misst Akkuspannung
  Pin temperatureMd       = Pin(  A5,     INPUT,         ANALOG   );  // misst Temperatur nahe den Motortreibern
  Pin buzzer              = Pin(  34,     OUTPUT,        DIGITAL  );  // piept Ton, aktiver Buzzer

  // Ausgabe
  Pin indFront            = Pin(  49,     OUTPUT,        DIGITAL  );  // ungenutzte LED vorne
  Pin speaker             = Pin(  13,     OUTPUT,        PWM      );  // zum abspielen von Tönen und Melodien, passiver Buzzer
  Pin indLeft             = Pin(  6,      OUTPUT,        PWM      );  // ungenutzte LED hinten links
  Pin indRight            = Pin(  38,     OUTPUT,        DIGITAL  );  // ungenutzte LED hinten rechts
  Pin indRgb              = Pin(  36,     OUTPUT,        DIGITAL  );  // stellt RGB-LEDs vorne auf Main-PCB ein, kann über Logic Analyser mitgelesen werden
  Pin indHearbeat         = Pin(  7,      OUTPUT,        PWM      );  // Blinken zweier LEDs

  // Bluetooth
  Pin bluetoothTx         = Pin(  16,     INPUT,         DIGITAL  );  // HC-05 <- Mega, Funkverbindung mit Partner
  Pin bluetoothRx         = Pin(  17,     INPUT,         DIGITAL  );  // HC-05 -> Mega, Funkverbindung mit Partner

  // Bodensensor
  Pin lineInterrupt       = Pin(  3,      INPUT,         PWM      );  // empfängt Interrupt beim Erkennen einer Linie
  Pin lineLight           = Pin(  46,     OUTPUT,        DIGITAL  );  // stellt Bodenbeleuchtungs-LEDs ein
  Pin lineTx              = Pin(  14,     INPUT,         DIGITAL  );  // Nano <- Mega
  Pin lineRx              = Pin(  15,     INPUT,         DIGITAL  );  // Nano -> Mega

  // Freigelegte Pins
  Pin test1               = Pin(  42,     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)
  Pin test2               = Pin(  44,     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)
  Pin test3               = Pin(  48,     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)
  Pin jumper1             = Pin(  39,     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J12)
  Pin jumper2             = Pin(  41,     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J13)
  Pin jumper3             = Pin(  43,     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J8)
  Pin jumper4             = Pin(  45,     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J9)
  Pin jumper5             = Pin(  A12,    OUTPUT,        ANALOG   );  // ungenutzter Analoganschluss mit Masse J24)
  Pin jumper6             = Pin(  A14,    OUTPUT,        ANALOG   );  // ungenutzter Analoganschluss mit Masse J26)

  // I2C
  Pin scl                 = Pin(  21,     INPUT_PULLUP,  DIGITAL  );  // I2C Clockleitung
  Pin sda                 = Pin(  20,     INPUT_PULLUP,  DIGITAL  );  // I2C Datenleitung

  // Positionslichter
  Pin navigationAntennaB  = Pin(  A8,     INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
  Pin navigationAntennaA  = Pin(  A9,     INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
  Pin navigationAntennaC  = Pin(  A7,     INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
  Pin navigationAntennaD  = Pin(  A6,     INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
  Pin navigationLight     = Pin(  4,      OUTPUT,        PWM      );  // aktiviert Pulse-IR-Positionslichter

  // Lichtschranke
  Pin lightBeamTx         = Pin(  47,     INPUT,         DIGITAL  );  // leuchtet den Ball an, Sensor misst Reflexion
  Pin lightBeamRx         = Pin(  A15,    INPUT,         ANALOG   );  // Fotowiderstand misst Helligkeit der Lichtschranke

  // Logger
  Pin loggerTx            = Pin(  18,     INPUT,         DIGITAL  );  // Logger <- Mega, Black Box Ereignissprotokoll
  Pin loggerRx            = Pin(  19,     INPUT,         DIGITAL  );  // Logger -> Mega, Black Box Ereignissprotokoll

  // Logic Analyser
  Pin loggerTrigger       = Pin(  40,     OUTPUT,        DIGITAL  );  // Freier Pin am Analyzer, kann zum auslösen einer Messung verwendet werden

  // Motortreiber
  Pin m0Speed             = Pin(  8,      OUTPUT,        PWM      );  // setzt Motordrehzahl
  Pin m0Dir1              = Pin(  25,     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m0Dir2              = Pin(  23,     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m0Current           = Pin(  A1,     INPUT,         ANALOG   );  // misst Stromstärke der Motoren
  Pin m1Speed             = Pin(  9,      OUTPUT,        PWM      );  // setzt Motordrehzahl
  Pin m1Dir1              = Pin(  29,     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m1Dir2              = Pin(  27,     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m1Current           = Pin(  A2,     INPUT,         ANALOG   );  // misst Stromstärke der Motoren
  Pin m2Speed             = Pin(  10,     OUTPUT,        PWM      );  // setzt Motordrehzahl
  Pin m2Dir1              = Pin(  37,     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m2Dir2              = Pin(  35,     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m2Current           = Pin(  A3,     INPUT,         ANALOG   );  // misst Stromstärke der Motoren
  Pin m3Speed             = Pin(  11,     OUTPUT,        PWM      );  // setzt Motordrehzahl
  Pin m3Dir1              = Pin(  33,     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m3Dir2              = Pin(  31,     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m3Current           = Pin(  A4,     INPUT,         ANALOG   );  // misst Stromstärke der Motoren

  // PUI-Anschluss
  Pin puiLight            = Pin(  32,     OUTPUT,        DIGITAL  );  // stellt PUI-LEDs ein
  Pin puiInterrupt        = Pin(  2,      INPUT,         DIGITAL  );  // empfängt Interrupt bei Knopfdruck
  Pin puiPoti             = Pin(  A0,     INPUT,         ANALOG   );  // misst Drehwiderstand

  // Schuss-Elektronik
  Pin kick                = Pin(  12,     OUTPUT,        PWM      );  // Schuss auslösen, lässt Elektromagneten anziehen, Wenn MOSFET ausgewählt PWM-fähig

  // Servo
  Pin cameraServo         = Pin(  5,      OUTPUT,        PWM      );  // Kamerawinkel, setzt Servolenkung für die Kameradrehung

  // SPI 
  Pin spiClk              = Pin(  52,     INPUT,         DIGITAL  );  // Serial Clock
  Pin spiCs               = Pin(  53,     OUTPUT,        DIGITAL  );  // Chip Select
  Pin spiMiso             = Pin(  50,     INPUT,         DIGITAL  );  // Master Input, Slave Output
  Pin spiMosi             = Pin(  51,     INPUT,         DIGITAL  );  // Master Output, Slave Input

  // USB 
  Pin usbTx               = Pin(  1,      INPUT,         DIGITAL  );  // Computer <- Mega, Computer Kommunikation
  Pin usbRx               = Pin(  0,      OUTPUT,        DIGITAL  );  // Computer -> Mega, Computer Kommunikation   

  // PUI: Keys and levers
  Key decreasePage          = Key(  A0,   0,     500,   200   );  // vorherige Bildschirmseite
  Key increasePage          = Key(  A0,   0,     500,   200   );  // nächste   Bildschirmseite
  Key selectPage            = Key(  A0,   0,     5000         );  // Seite auswählen
  Key resetProperties       = Key(  A0,   2000                );  // Alle Konfigurationen und Kalibrierungen zurücksetzten
  Key decreaseMenu          = Key(  26,   0                   );  // vorheriger Menüpunkt (misst Drehung des Rotary Encoders)
  Key increaseMenu          = Key(  28,   0                   );  // nächster   Menüpunkt (misst Drehung des Rotary Encoders)
  Key selectMenu            = Key(  30,   0,     1000         );  // Menüpunkt auswählen (Knopf des Rotary Encoders)
  Key testKick              = Key(  A0,   0,     1000,  0     );  // Schuss austesten
  Key compassCalibration    = Key(  A0,   0,     0,     0     );  // Torrichtung kalibrieren
  Key animation             = Key(  A0,   0                   );  // Starte Leucht Animation
  Key lineCalibration       = Key(  A0,   0,     500          );  // Linienhelligkeit kalibrieren
  Key lightBeamCalibration  = Key(  A0,   0,     500          );  // Lichtschranke kalibrieren
  Key start                 = Key(  22,   0                   );  // Losfahren
  Key stop                  = Key(  24,   0                   );  // Anhalten
  Key record                = Key(  A0,   0                   );  // Spiel aufzeichnen (start + stop)
  Key headstart             = Key(  A0,   0                   );  // headstart (lever)
  Key motor                 = Key(  A0,   0                   );  // motor     (lever)
  Key bluetooth             = Key(  A0,   0                   );  // bluetooth (lever)
  Key kicker                = Key(  A0,   0                   );  // kicker    (lever)
  Key bottom                = Key(  A0,   0                   );  // bottom    (lever)
  Key debug                 = Key(  A0,   0                   );  // debug     (lever)

  void update();

private:

};
#endif
