#ifndef IO_h
#define IO_h

#include "Timer.h"
#include "Shortcut.h"

class IO {
  public:
    IO();

    // Analoge Sensoren
    OwnPin temperaturePcb      = OwnPin(  A13,  INPUT,         ANALOG   );  // misst Temperatur nahe den Motortreibern
    OwnPin brightnessPcb       = OwnPin(  A10,  INPUT_PULLUP,  ANALOG   );  // misst Helligkeit rechts auf der Platine
    OwnPin batteryVoltmeter    = OwnPin(  A11,  INPUT,         ANALOG   );  // misst Akkuspannung
    OwnPin temperatureMd       = OwnPin(   A5,  INPUT,         ANALOG   );  // misst Temperatur nahe den Motortreibern
    OwnPin buzzer              = OwnPin(   34,  OUTPUT,        DIGITAL  );  // piept Ton, aktiver Buzzer

    // Ausgabe
    OwnPin indFront            = OwnPin(   49,  OUTPUT,        DIGITAL  );  // ungenutzte LED vorne
    OwnPin speaker             = OwnPin(   13,  OUTPUT,        PWM      );  // zum abspielen von Tönen und Melodien, passiver Buzzer
    OwnPin indLeft             = OwnPin(    6,  OUTPUT,        PWM      );  // ungenutzte LED hinten links
    OwnPin indRight            = OwnPin(   38,  OUTPUT,        DIGITAL  );  // ungenutzte LED hinten rechts
    OwnPin indRgb              = OwnPin(   36,  OUTPUT,        DIGITAL  );  // stellt RGB-LEDs vorne auf Main-PCB ein, kann über Logic Analyser mitgelesen werden
    OwnPin indHeartbeat        = OwnPin(    7,  OUTPUT,        PWM      );  // Blinken zweier LEDs

    // Bluetooth
    OwnPin bluetoothTx         = OwnPin(   16,  INPUT,         DIGITAL  );  // HC-05 <- Mega, Funkverbindung mit Partner
    OwnPin bluetoothRx         = OwnPin(   17,  INPUT,         DIGITAL  );  // HC-05 -> Mega, Funkverbindung mit Partner

    // Bodensensor
    OwnPin lineInterrupt       = OwnPin(    3,  INPUT,         PWM      );  // empfängt Interrupt beim Erkennen einer Linie
    OwnPin lineLight           = OwnPin(   46,  OUTPUT,        DIGITAL  );  // stellt Bodenbeleuchtungs-LEDs ein
    OwnPin lineTx              = OwnPin(   14,  INPUT,         DIGITAL  );  // Nano <- Mega
    OwnPin lineRx              = OwnPin(   15,  INPUT,         DIGITAL  );  // Nano -> Mega

    // Freigelegte Pins
    OwnPin test1               = OwnPin(   42,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)
    OwnPin test2               = OwnPin(   44,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)
    OwnPin test3               = OwnPin(   48,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)
    OwnPin jumper1             = OwnPin(   39,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J12)
    OwnPin jumper2             = OwnPin(   41,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J13)
    OwnPin jumper3             = OwnPin(   43,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J8)
    OwnPin jumper4             = OwnPin(   45,  OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J9)
    OwnPin jumper5             = OwnPin(  A12,  OUTPUT,        ANALOG   );  // ungenutzter Analoganschluss mit Masse J24)
    OwnPin jumper6             = OwnPin(  A14,  OUTPUT,        ANALOG   );  // ungenutzter Analoganschluss mit Masse J26)

    // I2C
    OwnPin scl                 = OwnPin(   21,  INPUT_PULLUP,  DIGITAL  );  // I2C Clockleitung
    OwnPin sda                 = OwnPin(   20,  INPUT_PULLUP,  DIGITAL  );  // I2C Datenleitung

    // Positionslichter
    OwnPin navigationAntennaB  = OwnPin(   A8,  INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
    OwnPin navigationAntennaA  = OwnPin(   A9,  INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
    OwnPin navigationAntennaC  = OwnPin(   A7,  INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
    OwnPin navigationAntennaD  = OwnPin(   A6,  INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
    OwnPin navigationLight     = OwnPin(    4,  OUTPUT,        PWM      );  // aktiviert Pulse-IR-Positionslichter

    // Lichtschranke
    OwnPin ballLight           = OwnPin(   47,  OUTPUT,        DIGITAL  );  // leuchtet den Ball an, Sensor misst Reflexion
    OwnPin ballTouch           = OwnPin(  A15,  INPUT_PULLUP,  ANALOG   );  // Fotowiderstand misst Helligkeit der Lichtschranke

    // Logger
    OwnPin loggerTx            = OwnPin(   18,  INPUT,         DIGITAL  );  // Logger <- Mega, Black Box Ereignissprotokoll
    OwnPin loggerRx            = OwnPin(   19,  INPUT,         DIGITAL  );  // Logger -> Mega, Black Box Ereignissprotokoll

    // Logic Analyser
    OwnPin loggerTrigger       = OwnPin(   40,  OUTPUT,        DIGITAL  );  // Freier OwnPin am Analyzer, kann zum auslösen einer Messung verwendet werden

    // Motortreiber
    OwnPin m0Speed             = OwnPin(    8,  OUTPUT,        PWM      );  // setzt Motordrehzahl
    OwnPin m0Dir1              = OwnPin(   25,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    OwnPin m0Dir2              = OwnPin(   23,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    OwnPin m0Current           = OwnPin(   A1,  INPUT,         ANALOG   );  // misst Stromstärke der Motoren
    OwnPin m1Speed             = OwnPin(    9,  OUTPUT,        PWM      );  // setzt Motordrehzahl
    OwnPin m1Dir1              = OwnPin(   29,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    OwnPin m1Dir2              = OwnPin(   27,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    OwnPin m1Current           = OwnPin(   A2,  INPUT,         ANALOG   );  // misst Stromstärke der Motoren
    OwnPin m2Speed             = OwnPin(   10,  OUTPUT,        PWM      );  // setzt Motordrehzahl
    OwnPin m2Dir1              = OwnPin(   37,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    OwnPin m2Dir2              = OwnPin(   35,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    OwnPin m2Current           = OwnPin(   A3,  INPUT,         ANALOG   );  // misst Stromstärke der Motoren
    OwnPin m3Speed             = OwnPin(   11,  OUTPUT,        PWM      );  // setzt Motordrehzahl
    OwnPin m3Dir1              = OwnPin(   33,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    OwnPin m3Dir2              = OwnPin(   31,  OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
    OwnPin m3Current           = OwnPin(   A4,  INPUT,         ANALOG   );  // misst Stromstärke der Motoren

    // PUI-Anschluss
    OwnPin puiLight            = OwnPin(   32,  OUTPUT,        DIGITAL  );  // stellt PUI-LEDs ein
    OwnPin puiInterrupt        = OwnPin(    2,  INPUT,         DIGITAL  );  // empfängt Interrupt bei Knopfdruck
    OwnPin poti                = OwnPin(   A0,  INPUT,         ANALOG   );  // misst Drehwiderstand
    OwnPin headstart           = OwnPin(    0,  INPUT_PULLUP,  PUI      );  // headstart (lever)
    OwnPin motor               = OwnPin(    1,  INPUT_PULLUP,  PUI      );  // motor     (lever)
    OwnPin bluetooth           = OwnPin(    2,  INPUT_PULLUP,  PUI      );  // bluetooth (lever)
    OwnPin kicker              = OwnPin(    3,  INPUT_PULLUP,  PUI      );  // kicker    (lever)
    OwnPin bottom              = OwnPin(    4,  INPUT_PULLUP,  PUI      );  // bottom    (lever)
    OwnPin turbo               = OwnPin(    5,  INPUT_PULLUP,  PUI      );  // debug     (lever)

    OwnPin indKeeper           = OwnPin(    6,  OUTPUT,        PUI      );  // kleine Led
    OwnPin indStriker          = OwnPin(    7,  OUTPUT,        PUI      );  // große Led


    // Schuss-Elektronik
    OwnPin kick                = OwnPin(   12,  OUTPUT,        PWM      );  // Schuss auslösen, lässt Elektromagneten anziehen, Wenn MOSFET ausgewählt PWM-fähig

    // Servo
    OwnPin cameraServo         = OwnPin(    5,  OUTPUT,        PWM      );  // Kamerawinkel, setzt Servolenkung für die Kameradrehung

    // SPI 
    OwnPin spiClk              = OwnPin(   52,  INPUT,         DIGITAL  );  // Serial Clock
    OwnPin spiCs               = OwnPin(   53,  OUTPUT,        DIGITAL  );  // Chip Select
    OwnPin spiMiso             = OwnPin(   50,  INPUT,         DIGITAL  );  // Master Input, Slave Output
    OwnPin spiMosi             = OwnPin(   51,  INPUT,         DIGITAL  );  // Master Output, Slave Input

    // USB 
    OwnPin usbTx               = OwnPin(    1,  INPUT,         DIGITAL  );  // Computer <- Mega, Computer Kommunikation
    OwnPin usbRx               = OwnPin(    0,  OUTPUT,        DIGITAL  );  // Computer -> Mega, Computer Kommunikation   

    // PUI: keys and levers
    Key decreasePage          = Key(   11,  PUI,      0,     500,   200   );  // vorherige Bildschirmseite
    Key increasePage          = Key(   9,  PUI,      0,     500,   200   );  // nächste   Bildschirmseite
    Key selectPage            = Key(   10,  PUI,      0,     5000         );  // Seite auswählen
    Key decreaseMenu          = Key(  26,  DIGITAL,  0                   );  // vorheriger Menüpunkt (misst Drehung des Rotary Encoders)
    Key increaseMenu          = Key(  28,  DIGITAL,  0                   );  // nächster   Menüpunkt (misst Drehung des Rotary Encoders)
    Key selectMenu            = Key(  30,  DIGITAL,  0,     1000         );  // Menüpunkt auswählen (Knopf des Rotary Encoders)
    Key testKick              = Key(   8,  PUI,      0,     0,  0        );  // Schuss austesten 
    Key compassCalibration    = Key(  12,  PUI,      0,     0,     0     );  // Torrichtung kalibrieren
    Key animation             = Key(  13,  PUI,      0                   );  // Starte Leucht Animation
    Key lineCalibration       = Key(  14,  PUI,      0,     500          );  // Linienhelligkeit kalibrieren
    Key ballTouchCalibration  = Key(  15,  PUI,      0,     500          );  // Lichtschranke kalibrieren
    Key start                 = Key(  22,  DIGITAL,  0                   );  // Losfahren
    Key stop                  = Key(  24,  DIGITAL,  0                   );  // Anhalten

    // PUI: shortcuts
    Key *_record           [2]  = {  &start ,         &stop          }; Shortcut  record           = Shortcut(  _record,           2,  FIRE_KEYS,     0              );  // Spiel aufzeichnen (start + stop)
    Key *_resetProperties  [2]  = {  &decreasePage,  &increasePage  }; Shortcut  resetProperties  = Shortcut(  _resetProperties,  2,  MUTE_KEYS,  2000              );  // Alle Konfigurationen und Kalibrierungen zurücksetzten
    Key *_kickerStart      [2]  = {  &increasePage,      &start         }; Shortcut  kickerStart      = Shortcut(  _kickerStart,      2,  MUTE_KEYS,     0              );  // aktiviere einen dauerhaften Schuss
    Key *_kickerStop       [2]  = {  &increasePage,      &stop          }; Shortcut  kickerStop       = Shortcut(  _kickerStop,       2,  MUTE_KEYS,     0              );  // deaktiviere einen dauerhaften Schuss
    Key *_shiftStart       [2]  = {  &selectMenu,    &start         }; Shortcut  shiftStart       = Shortcut(  _shiftStart,       2,  MUTE_KEYS,     0,  200,  50  );  // 
    Key *_shiftStop        [2]  = {  &selectMenu,    &stop          }; Shortcut  shiftStop        = Shortcut(  _shiftStop,        2,  MUTE_KEYS,     0,  600,  50  );  // 

    void update();



    // binary timers
    Timer flat            = Timer(    600             );  // liegen wir flach?
    Timer isHeadstart     = Timer(    350             );  // führen wir einen Schnellstart aus ?
    Timer isDodge         = Timer(    200             );  // weichen wir dem Gegner aus?
    Timer hasBall         = Timer(     80             );  // haben wir Ballbesitz?
    Timer runtime         = Timer(                    );  // Laufzeit der Schleife 
    Timer seeBall         = Timer(    100,  &flat     );  // sehen wir den Ball?
    Timer seeGoal         = Timer(    500,  &flat     );  // sehen wir das Tor?
    Timer seeMate         = Timer(    100,  &flat     );  // sehen wir ein Positionslicht
    Timer closeBall       = Timer(    500,  &seeBall  );  // ist der Ball nahe?
    Timer drift           = Timer(    200             );  // müssen wir ein Driften verhindern?
    Timer seeBallLeft     = Timer(      0,  &seeBall  );  // ist der Ball links?
    Timer seeBallRight    = Timer(      0,  &seeBall  );  // ist der Ball rechts?
    Timer seeBallCenter   = Timer(      0,  &seeBall  );  // ist der Ball mittig?
    Timer cameraResponse  = Timer(  20000             );  // ist die Kamera verbunden?
    Timer driveLocked     = Timer(    300             );  // dürfen neue Steuerwerte esetzt werden?
    Timer setupLight      = Timer(    200             );
    Timer kickActive      = Timer(     50             );
    Timer lineDetected    = Timer(    200             );
    Timer lineAvoid       = Timer(    150             );
    Timer sendHeartBeat   = Timer(    250             );  // wurde Heartbeat des Gegners empfangen?
    Timer bluetoothSend   = Timer(    100             );  // sollen Bluetooth-Updates gesendet werden? 
    Timer farSidelineRight= Timer(    100             );  // befinden wir uns am rechten seitlichen Rand des Spielfeldes
    Timer farSidelineLeft = Timer(    100             );  // befinden wir uns am linken seitlichen Rand des Spielfeldes
    Timer onLine          = Timer(    300             );
    Timer abc             = Timer(    100             );

    // all global variables
    bool  aggressive;
    bool  striker;
    Value state          = Value(      LIMITS,    0,    9  );
    Value stateDirection = Value(     BOOLEAN              );

    Value driveAngle     = Value(  MODULATION,    0,  359  );  // Zielwinkel
    Value driveOrientation=Value(  MODULATION, -179,  180  );  // Ziel-Orientierungswinkel
    Value drivePower     = Value(      LIMITS,    0,  255  );  // Geschwindigkeit
    Value driveRotation  = Value(      LIMITS, -255,  255  );  // Eigenrotation -> Korrekturdrehung, um wieder zum Gegnertor ausgerichtet zu sein
    Value driveEnabled   = Value(     BOOLEAN              );  // Aktivierung des Fahrgestells

    Value ball           = Value(      LIMITS, -160,  159  );  // Abweichung der Ball X-Koordinate
    Value ballWidth      = Value(      LIMITS,    0        );  // Ballbreite
    Value ballArea       = Value(      LIMITS,    0        );  // Ballgröße (Flächeninhalt)
    Value goal           = Value(      LIMITS, -160,  159  );  // Abweichung der Tor X-Koordinate
    Value goalWidth      = Value(      LIMITS,    0        );  // Torbreite
    Value goalArea       = Value(      LIMITS,    0        );  // Torgröße (Flächeninhalt)
  
    Value segment        = Value(      LIMITS,    0,    2  );  // Laufzeit eines Codeblockes
    Value battery        = Value(     BOOLEAN              );  // ist der Akku angeschlosse?
    Value batteryVoltage = Value(      LIMITS,     0,  999 );
    bool  pause;  // ist das Spiel pausiert?

    Value heading        = Value(  MODULATION, -179,  180  );
    Value headingOffset  = Value(  MODULATION, -179,  180  );
    Value xOrientation   = Value(  MODULATION, -179,  180  );
    Value yOrientation   = Value(  MODULATION, -179,  180  );
    Value zOrientation   = Value(  MODULATION, -179,  180  );

    Value distanceFront  = Value(  MODULATION,    0,  MAX_DISTANCE);
    Value distanceBack   = Value(  MODULATION,    0,  MAX_DISTANCE);
    Value distanceRight  = Value(  MODULATION,    0,  MAX_DISTANCE);
    Value distanceLeft   = Value(  MODULATION,    0,  MAX_DISTANCE);

    Value kickPermanent  = Value(     BOOLEAN              );

    Value lineAngle      = Value(  MODULATION,  -179, 180  );

    Value animationState = Value(                          );
    Value animationEnabled = Value(   BOOLEAN              );

    Value partnerRating  = Value(      LIMITS,    0,  255  );
  private:
};
extern IO io;

#endif