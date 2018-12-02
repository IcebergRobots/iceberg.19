#ifndef IO_h
#define IO_h

#include "Core.h"

class IO
{
public:
  IO();

  // Analoge Sensoren
  Pin temperaturePcb      = temperaturePcb      (  A13    INPUT,         ANALOG   );  // misst Temperatur nahe den Motortreibern
  Pin brightnessPcb       = brightnessPcb       (  A10    INPUT_PULLUP,  ANALOG   );  // misst Helligkeit rechts auf der Platine
  Pin batteryVoltage      = batteryVoltage      (  A11    INPUT,         ANALOG   );  // misst Akkuspannung
  Pin temperatureMd       = temperatureMd       (  A5     INPUT,         ANALOG   );  // misst Temperatur nahe den Motortreibern
  Pin buzzer              = buzzer              (  34     OUTPUT,        DIGITAL  );  // piept Ton, aktiver Buzzer

  // Ausgabe
  Pin indFront            = indFront            (  49     OUTPUT,        DIGITAL  );  // ungenutzte LED vorne
  Pin speaker             = speaker             (  13     OUTPUT,        DIGITAL  );  // zum abspielen von Tönen und Melodien, passiver Buzzer
  Pin indLeft             = indLeft             (  6      OUTPUT,        DIGITAL  );  // ungenutzte LED hinten links
  Pin indRight            = indRight            (  38     OUTPUT,        DIGITAL  );  // ungenutzte LED hinten rechts
  Pin indRgb              = indRgb              (  36     OUTPUT,        DIGITAL  );  // stellt RGB-LEDs vorne auf Main-PCB ein, kann über Logic Analyser mitgelesen werden
  Pin indHearbeat         = indHearbeat         (  7      OUTPUT,        DIGITAL  );  // Blinken zweier LEDs

  // Bluetooth
  Pin bluetoothTx         = bluetoothTx         (  TX2    INPUT,         DIGITAL  );  // HC-05 <- Mega, Funkverbindung mit Partner
  Pin bluetoothRx         = bluetoothRx         (  RX2    INPUT,         DIGITAL  );  // HC-05 -> Mega, Funkverbindung mit Partner

  // Bodensensor
  Pin lineInterrupt       = lineInterrupt       (  3      INPUT,         DIGITAL  );  // empfängt Interrupt beim Erkennen einer Linie
  Pin lineLight           = lineLight           (  46     OUTPUT,        DIGITAL  );  // stellt Bodenbeleuchtungs-LEDs ein
  Pin lineRx              = lineRx              (  15     INPUT,         DIGITAL  );  // Nano -> Mega
  Pin lineTx              = lineTx              (  14     INPUT,         DIGITAL  );  // Nano <- Mega
  Pin test1               = test1               (  42     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)

  // Freigelegte Pins
  Pin test3               = test3               (  48     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)
  Pin test2               = test2               (  44     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss Testpin)
  Pin jumper2             = jumper2             (  41     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J13)
  Pin jumper1             = jumper1             (  39     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J12)
  Pin jumper4             = jumper4             (  45     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J9)
  Pin jumper3             = jumper3             (  43     OUTPUT,        DIGITAL  );  // ungenutzter Digitalanschluss mit Masse J8)
  Pin jumper2             = jumper2             (  A14    OUTPUT,        ANALOG   );  // ungenutzter Analoganschluss mit Masse J26)
  Pin jumper1             = jumper1             (  A12    OUTPUT,        ANALOG   );  // ungenutzter Analoganschluss mit Masse J24)

  // I2C
  Pin scl                 = scl                 (  21     INPUT_PULLUP,  DIGITAL  );  // I2C Clockleitung
  Pin sda                 = sda                 (  20     INPUT_PULLUP,  DIGITAL  );  // I2C Datenleitung

  // Positionslichter
  Pin navigationAntennaB  = navigationAntennaB  (  A8     INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
  Pin navigationAntennaA  = navigationAntennaA  (  A9     INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
  Pin navigationAntennaC  = navigationAntennaC  (  A7     INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
  Pin navigationAntennaD  = navigationAntennaD  (  A6     INPUT,         ANALOG   );  // erkennt Entfernung der IR-Pulsquelle
  Pin navigationLight     = navigationLight     (  4      OUTPUT,        DIGITAL  );  // aktiviert Pulse-IR-Positionslichter

  // Lichtschranke
  Pin lightBeamTx         = lightBeamTx         (  47     INPUT,         DIGITAL  );  // leuchtet den Ball an, Sensor misst Reflexion
  Pin lightBeamRx         = lightBeamRx         (  A15    INPUT,         ANALOG   );  // Fotowiderstand misst Helligkeit der Lichtschranke

  // Logger
  Pin loggerTx            = loggerTx            (  18     INPUT,         DIGITAL  );  // Logger <- Mega, Black Box Ereignissprotokoll
  Pin loggerRx            = loggerRx            (  19     INPUT,         DIGITAL  );  // Logger -> Mega, Black Box Ereignissprotokoll

  // Logic Analyser
  Pin loggerTrigger       = loggerTrigger       (  40     OUTPUT,        DIGITAL  );  // Freier Pin am Analyzer, kann zum auslösen einer Messung verwendet werden

  // Motortreiber
  Pin m0Speed             = m0Speed             (  8      OUTPUT,        DIGITAL  );  // setzt Motordrehzahl
  Pin m0Dir1              = m0Dir1              (  25     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m0Dir2              = m0Dir2              (  23     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m0Current           = m0Current           (  A1     INPUT,         ANALOG   );  // misst Stromstärke der Motoren
  Pin m1Speed             = m1Speed             (  9      OUTPUT,        DIGITAL  );  // setzt Motordrehzahl
  Pin m1Dir1              = m1Dir1              (  29     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m1Dir2              = m1Dir2              (  27     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m1Current           = m1Current           (  A2     INPUT,         ANALOG   );  // misst Stromstärke der Motoren
  Pin m2Speed             = m2Speed             (  10     OUTPUT,        DIGITAL  );  // setzt Motordrehzahl
  Pin m2Dir1              = m2Dir1              (  37     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m2Dir2              = m2Dir2              (  35     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m2Current           = m2Current           (  A3     INPUT,         ANALOG   );  // misst Stromstärke der Motoren
  Pin m3Speed             = m3Speed             (  11     OUTPUT,        DIGITAL  );  // setzt Motordrehzahl
  Pin m3Dir1              = m3Dir1              (  33     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m3Dir2              = m3Dir2              (  31     OUTPUT,        DIGITAL  );  // legt Fahrtrichtung oder Bremsmodus fest
  Pin m3Current           = m3Current           (  A4     INPUT,         ANALOG   );  // misst Stromstärke der Motoren

  // PUI-Anschluss
  Pin puiLight            = puiLight            (  32     OUTPUT,        DIGITAL  );  // stellt PUI-LEDs ein
  Pin puiRotButton        = puiRotButton        (  30     INPUT_PULLUP,  DIGITAL  );  // Knopf des Rotary Encoders
  Pin puiRotDir1          = puiRotDir1          (  26     INPUT_PULLUP,  DIGITAL  );  // misst Drehung des Rotary Encoders
  Pin puiRotDir2          = puiRotDir2          (  28     INPUT_PULLUP,  DIGITAL  );  // misst Drehung des Rotary Encoders
  Pin puiInterrupt        = puiInterrupt        (  2      INPUT,         DIGITAL  );  // empfängt Interrupt bei Knopfdruck
  Pin puiPoti             = puiPoti             (  A0     INPUT,         ANALOG   );  // misst Drehwiderstand
  Pin puiStart            = puiStart            (  22     INPUT_PULLUP,  DIGITAL  );  // startet Motoren
  Pin puiStop             = puiStop             (  24     INPUT_PULLUP,  DIGITAL  );  // stoppt Motoren

  // Schuss-Elektronik
  Pin kick                = kick                (  12     OUTPUT,        DIGITAL  );  // Schuss auslösen, lässt Elektromagneten anziehen, Wenn MOSFET ausgewählt PWM-fähig

  // Servo
  Pin cameraServo         = cameraServo         (  5      OUTPUT,        DIGITAL  );  // Kamerawinkel, setzt Servolenkung für die Kameradrehung

  // SPI 
  Pin spiClk              = spiClk              (  52     INPUT,         DIGITAL  );  // Serial Clock
  Pin spiCs               = spiCs               (  53     OUTPUT,        DIGITAL  );  // Chip Select
  Pin spiMiso             = spiMiso             (  50     INPUT,         DIGITAL  );  // Master Input, Slave Output
  Pin spiMosi             = spiMosi             (  51     INPUT,         DIGITAL  );  // Master Output, Slave Input

  // USB 
  Pin usbTx               = usbTx               (  1      INPUT,         DIGITAL  );  // Computer <- Mega, Computer Kommunikation
  Pin usbRx               = usbRx               (  0      OUTPUT,        DIGITAL  );  // Computer -> Mega, Computer Kommunikation   
	
  /*
  Key decreasePage = Key(PUI_POTI, 0, 500, 200);   // decreasePage
  Key increasePage = Key(PUI_POTI, 0, 500, 200);   // increasePage
  Key selectPage = Key(PUI_POTI, 0);               // selectPage
  Key resetProperties = Key(PUI_POTI, 2000);       // resetProperties (left + right)
  Key selectMenu = Key(PUI_ROT_BUTTON, 0, 1000);   // selectMenu
  Key kick = Key(PUI_POTI, 0, 1000, 0);            // kick
  Key compassCalibration = Key(PUI_POTI, 0, 0, 0); // compassCalibration
  Key animation = Key(PUI_POTI, 0);                // animation
  Key lineCalibration = Key(PUI_POTI, 500);        // lineCalibration
  Key lightBeamCalibration = Key(PUI_POTI, 500);   // lightBeamCalibration
  Key start = Key(PUI_START, 0);                   // start
  Key stop = Key(PUI_STOP, 0);                     // stop
  Key record = Key(PUI_POTI, 0, 0, 0);             // record (start + stop)
  Key headstart = Key(PUI_POTI, 0);                // headstart (lever)
  Key motor = Key(PUI_POTI, 0);                    // motor     (lever)
  Key bluetooth = Key(PUI_POTI, 0);                // bluetooth (lever)
  Key kicker = Key(PUI_POTI, 0);                   // kicker    (lever)
  Key bottom = Key(PUI_POTI, 0);                   // bottom    (lever)
  Key debug = Key(PUI_POTI, 0);                    // debug     (lever)
  */
  void update();

private:

};
#endif
