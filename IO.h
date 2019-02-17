#ifndef IO_h
#define IO_h

#include "Input/Timer.h"
#include "Input/Shortcut.h"

class IO {
  public:
    IO();

    // Analoge Sensoren
    Pin temperaturePcb      = Pin(  A13,  INPUT,         ANALOG   );  // misst Temperatur nahe den Motortreibern
    Pin brightnessPcb       = Pin(  A10,  INPUT_PULLUP,  ANALOG   );  // misst Helligkeit rechts auf der Platine
    Pin batteryVoltage      = Pin(  A11,  INPUT,         ANALOG   );  // misst Akkuspannung
    Pin temperatureMd       = Pin(   A5,  INPUT,         ANALOG   );  // misst Temperatur nahe den Motortreibern
    Pin buzzer              = Pin(   34,  OUTPUT,        DIGITAL  );  // piept Ton, aktiver Buzzer

    // Ausgabe
    Pin indFront            = Pin(   49,  OUTPUT,        DIGITAL  );  // ungenutzte LED vorne
    Pin speaker             = Pin(   13,  OUTPUT,        PWM      );  // zum abspielen von Tönen und Melodien, passiver Buzzer
    Pin indLeft             = Pin(    6,  OUTPUT,        PWM      );  // ungenutzte LED hinten links
    Pin indRight            = Pin(   38,  OUTPUT,        DIGITAL  );  // ungenutzte LED hinten rechts
    Pin indRgb              = Pin(   36,  OUTPUT,        DIGITAL  );  // stellt RGB-LEDs vorne auf Main-PCB ein, kann über Logic Analyser mitgelesen werden
    Pin indHearbeat         = Pin(    7,  OUTPUT,        PWM      );  // Blinken zweier LEDs

    // Bluetooth
    Pin bluetoothTx         = Pin(   16,  INPUT,         DIGITAL  );  // HC-05 <- Mega, Funkverbindung mit Partner
    Pin bluetoothRx         = Pin(   17,  INPUT,         DIGITAL  );  // HC-05 -> Mega, Funkverbindung mit Partner

    // Bodensensor
    Pin lineInterrupt       = Pin(    3,  INPUT,         PWM      );  // empfängt Interrupt beim Erkennen einer Linie
    Pin lineLight           = Pin(   46,  OUTPUT,        DIGITAL  );  // stellt Bodenbeleuchtungs-LEDs ein
    Pin lineTx              = Pin(   14,  INPUT,         DIGITAL  );  // Nano <- Mega
    Pin lineRx              = Pin(   15,  INPUT,         DIGITAL  );  // Nano -> Mega

    // Freigelegte Pins
    Pin test1               = Pin(   42,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)
    Pin test2               = Pin(   44,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)
    Pin test3               = Pin(   48,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)
    Pin jumper1             = Pin(   39,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J12)
    Pin jumper2             = Pin(   41,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J13)
    Pin jumper3             = Pin(   43,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J8)
    Pin jumper4             = Pin(   45,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J9)
    Pin jumper5             = Pin(  A12,  OUTPUT,        ANALOG   );  // ungenutzter Analoganschluss mit Masse J24)
    Pin jumper6             = Pin(  A14,  OUTPUT,        ANALOG   );  // ungenutzter Analoganschluss mit Masse J26)

    // I2C
    Pin scl                 = Pin(   21,  INPUT_PULLUP,  DIGITAL  );  // I2C Clockleitung
    Pin sda                 = Pin(   20,  INPUT_PULLUP,  DIGITAL  );  // I2C Datenleitung

    // Positionslichter
    Pin navigationAntennaB  = Pin(   A8,  INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
    Pin navigationAntennaA  = Pin(   A9,  INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
    Pin navigationAntennaC  = Pin(   A7,  INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
    Pin navigationAntennaD  = Pin(   A6,  INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
    Pin navigationLight     = Pin(    4,  OUTPUT,        PWM      );  // aktiviert Pulse-IR-Positionslichter

    // Lichtschranke
    Pin ballLight           = Pin(   47,  OUTPUT,        DIGITAL  );  // leuchtet den Ball an, Sensor misst Reflexion
    Pin ballTouch           = Pin(  A15,  INPUT_PULLUP,  ANALOG   );  // Fotowiderstand misst Helligkeit der Lichtschranke

    // Logger
    Pin loggerTx            = Pin(   18,  INPUT,         DIGITAL  );  // Logger <- Mega, Black Box Ereignissprotokoll
    Pin loggerRx            = Pin(   19,  INPUT,         DIGITAL  );  // Logger -> Mega, Black Box Ereignissprotokoll

    // Logic Analyser
    Pin loggerTrigger       = Pin(   40,  OUTPUT,        DIGITAL  );  // Freier Pin am Analyzer, kann zum auslösen einer Messung verwendet werden

    // Motortreiber
    Pin m0Speed             = Pin(    8,  OUTPUT,        PWM      );  // setzt Motordrehzahl
    Pin m0Dir1              = Pin(   25,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    Pin m0Dir2              = Pin(   23,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    Pin m0Current           = Pin(   A1,  INPUT,         ANALOG   );  // misst Stromstärke der Motoren
    Pin m1Speed             = Pin(    9,  OUTPUT,        PWM      );  // setzt Motordrehzahl
    Pin m1Dir1              = Pin(   29,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    Pin m1Dir2              = Pin(   27,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    Pin m1Current           = Pin(   A2,  INPUT,         ANALOG   );  // misst Stromstärke der Motoren
    Pin m2Speed             = Pin(   10,  OUTPUT,        PWM      );  // setzt Motordrehzahl
    Pin m2Dir1              = Pin(   37,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    Pin m2Dir2              = Pin(   35,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    Pin m2Current           = Pin(   A3,  INPUT,         ANALOG   );  // misst Stromstärke der Motoren
    Pin m3Speed             = Pin(   11,  OUTPUT,        PWM      );  // setzt Motordrehzahl
    Pin m3Dir1              = Pin(   33,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    Pin m3Dir2              = Pin(   31,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    Pin m3Current           = Pin(   A4,  INPUT,         ANALOG   );  // misst Stromstärke der Motoren

    // PUI-Anschluss
    Pin puiLight            = Pin(   32,  OUTPUT,        DIGITAL  );  // stellt PUI-LEDs ein
    Pin puiInterrupt        = Pin(    2,  INPUT,         DIGITAL  );  // empfängt Interrupt bei Knopfdruck
    Pin poti                = Pin(   A0,  INPUT,         ANALOG   );  // misst Drehwiderstand
    Pin headstart           = Pin(    0,  INPUT_PULLUP,  PUI      );  // headstart (lever)
    Pin motor               = Pin(    1,  INPUT_PULLUP,  PUI      );  // motor     (lever)
    Pin bluetooth           = Pin(    2,  INPUT_PULLUP,  PUI      );  // bluetooth (lever)
    Pin kicker              = Pin(    3,  INPUT_PULLUP,  PUI      );  // kicker    (lever)
    Pin bottom              = Pin(    4,  INPUT_PULLUP,  PUI      );  // bottom    (lever)
    Pin turbo               = Pin(    5,  INPUT_PULLUP,  PUI      );  // debug     (lever)


    // Schuss-Elektronik
    Pin kick                = Pin(   12,  OUTPUT,        PWM      );  // Schuss auslösen, lässt Elektromagneten anziehen, Wenn MOSFET ausgewählt PWM-fähig

    // Servo
    Pin cameraServo         = Pin(    5,  OUTPUT,        PWM      );  // Kamerawinkel, setzt Servolenkung für die Kameradrehung

    // SPI 
    Pin spiClk              = Pin(   52,  INPUT,         DIGITAL  );  // Serial Clock
    Pin spiCs               = Pin(   53,  OUTPUT,        DIGITAL  );  // Chip Select
    Pin spiMiso             = Pin(   50,  INPUT,         DIGITAL  );  // Master Input, Slave Output
    Pin spiMosi             = Pin(   51,  INPUT,         DIGITAL  );  // Master Output, Slave Input

    // USB 
    Pin usbTx               = Pin(    1,  INPUT,         DIGITAL  );  // Computer <- Mega, Computer Kommunikation
    Pin usbRx               = Pin(    0,  OUTPUT,        DIGITAL  );  // Computer -> Mega, Computer Kommunikation   

    // PUI: keys and levers
    Key decreasePage          = Key(   0,  VIRTUAL,  0,     500,   200   );  // vorherige Bildschirmseite
    Key increasePage          = Key(   0,  PUI,      0,     500,   200   );  // nächste   Bildschirmseite
    Key selectPage            = Key(   0,  PUI,      0,     5000         );  // Seite auswählen
    Key decreaseMenu          = Key(  26,  DIGITAL,  0                   );  // vorheriger Menüpunkt (misst Drehung des Rotary Encoders)
    Key increaseMenu          = Key(  28,  DIGITAL,  0                   );  // nächster   Menüpunkt (misst Drehung des Rotary Encoders)
    Key selectMenu            = Key(  30,  DIGITAL,  0,     1000         );  // Menüpunkt auswählen (Knopf des Rotary Encoders)
    Key testKick              = Key(   0,  VIRTUAL,  0,     1000,  0     );  // Schuss austesten
    Key compassCalibration    = Key(   0,  VIRTUAL,  0,     0,     0     );  // Torrichtung kalibrieren
    Key animation             = Key(   0,  VIRTUAL,  0                   );  // Starte Leucht Animation
    Key lineCalibration       = Key(   6,  PUI,      0,     500          );  // Linienhelligkeit kalibrieren
    Key ballTouchCalibration  = Key(   7,  PUI,      0,     500          );  // Lichtschranke kalibrieren
    Key start                 = Key(  22,  DIGITAL,  0                   );  // Losfahren
    Key stop                  = Key(  24,  DIGITAL,  0                   );  // Anhalten

    // PUI: shortcuts
    Key *_record           [2]  = {  &start,         &stop          }; Shortcut  record           = Shortcut(  _record,           2,  FIRE_KEYS,     0              );  // Spiel aufzeichnen (start + stop)
    Key *_resetProperties  [2]  = {  &decreasePage,  &increasePage  }; Shortcut  resetProperties  = Shortcut(  _resetProperties,  2,  MUTE_KEYS,  2000              );  // Alle Konfigurationen und Kalibrierungen zurücksetzten
    Key *_kickerStart      [2]  = {  &testKick,      &start         }; Shortcut  kickerStart      = Shortcut(  _kickerStart,      2,  MUTE_KEYS,     0              );  // aktiviere einen dauerhaften Schuss
    Key *_kickerStop       [2]  = {  &testKick,      &stop          }; Shortcut  kickerStop       = Shortcut(  _kickerStop,       2,  MUTE_KEYS,     0              );  // deaktiviere einen dauerhaften Schuss
    Key *_shiftStart       [2]  = {  &selectMenu,    &start         }; Shortcut  shiftStart       = Shortcut(  _shiftStart,       2,  MUTE_KEYS,     0,  600,  200  );  // 
    Key *_shiftStop        [2]  = {  &selectMenu,    &stop          }; Shortcut  shiftStop        = Shortcut(  _shiftStop,        2,  MUTE_KEYS,     0,  600,  200  );  // 

    // binary timers
    Timer flat            = Timer(    600             );  // liegen wir flach?
    Timer onLine          = Timer(    300             );  // berühren wir die Linie?
    Timer isHeadstart     = Timer(    350             );  // führen wir einen Schnellstart aus ?
    Timer isDodge         = Timer(    200             );  // weichen wir dem Gegner aus?
    Timer hasBall         = Timer(     50             );  // haben wir Ballbesitz?
    Timer segment         = Timer(                    );  // Laufzeit eines Codeblockes
    Timer runtime         = Timer(                    );  // Laufzeit der Schleife 
    Timer seeBall         = Timer(    100,  &flat     );  // sehen wir den Ball?
    Timer seeGoal         = Timer(    500,  &flat     );  // sehen wir das Tor?
    Timer closeBall       = Timer(    500,  &seeBall  );  // ist der Ball nahe?
    Timer drift           = Timer(    200             );  // müssen wir ein Driften verhindern?
    Timer ballLeft        = Timer(      0,  &seeBall  );  // ist der Ball links?
    Timer ballRight       = Timer(      0,  &seeBall  );  // ist der Ball rechts?
    Timer ballCenter      = Timer(      0,  &seeBall  );  // ist der Ball mittig?
    Timer cameraResponse  = Timer(  20000             );  // ist die Kamera verbunden?
    Timer driveLocked     = Timer(    300             );  // dürfen neue Steuerwerte esetzt werden?

    // all global variables
    Value aggressive     = Value(     BOOLEAN                 );
    Value striker        = Value(     BOOLEAN                 );
    Value state          = Value(      LIMITS,      0,     9  );
    Value stateDirection = Value(     BOOLEAN                 );

    Value driveAngle     = Value(  MODULATION,      0,   359  ); // Zielwinkel
    Value drivePower     = Value(      LIMITS,      0,   255  ); // Geschwindigkeit
    Value driveRotation  = Value(      LIMITS,   -255,   255  ); // Eigenrotation -> Korrekturdrehung, um wieder zum Gegnertor ausgerichtet zu sein
    Value driveEnabled   = Value(     BOOLEAN                 ); // Aktivierung des Fahrgestells

    Value ball           = Value(      LIMITS,   -160,   159  );  // Abweichung der Ball X-Koordinate
    Value ballWidth      = Value(      LIMITS,      0         );  // Ballbreite
    Value ballArea       = Value(      LIMITS,      0         );  // Ballgröße (Flächeninhalt)
    Value goal           = Value(      LIMITS,   -160,   159  );  // Abweichung der Tor X-Koordinate
    Value goalWidth      = Value(      LIMITS,      0         );  // Torbreite
    Value goalArea       = Value(      LIMITS,      0         );  // Torgröße (Flächeninhalt)
    
    Value hasDebugHead   = Value(     BOOLEAN                 );  // Debug-Zeilenanfang
    Value battery        = Value(     BOOLEAN                 );  // ist der Akku angeschlosse?

    Value heading        = Value(  MODULATION,   -179,   180  );
    Value xOrientation   = Value(  MODULATION);
    Value yOrientation   = Value(  MODULATION);
    Value zOrientation   = Value(  MODULATION);

    void update();

  private:
};
extern IO io;

#endif