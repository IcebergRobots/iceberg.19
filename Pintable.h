#ifndef Pintable_h
#define Pintable_h

// Analoge Sensoren
#define BRIGHTNESS_PCB  A10 // misst Helligkeit rechts auf der Platine
#define TEMPERATURE_PCB A13 // misst Temperatur nahe den Motortreibern
#define TEMPERATURE_MD  A5  // misst Temperatur nahe den Motortreibern
#define BATTERY_VOLTAGE A11 // misst Akkuspannung

// Ausgabe
#define BUZZER          34  // piept Ton, aktiver Buzzer
#define SPEAKER         13  // zum abspielen von Tönen und Melodien, passiver Buzzer
#define IND_F           49  // ungenutzte LED vorne
#define IND_BR          38  // ungenutzte LED hinten rechts
#define IND_BL          6   // ungenutzte LED hinten links
#define IND_HEARBEAT    7   // Blinken zweier LEDs
#define IND_RGB         36  // stellt RGB-LEDs vorne auf Main-PCB ein, kann über Logic Analyser mitgelesen werden

// Bluetooth
#define BLUETOOTH_TX    TX2 // HC-05 <- Mega, Funkverbindung mit Partner
#define BLUETOOTH_RX    RX2 // HC-05 -> Mega, Funkverbindung mit Partner

// Bodensensor
#define LINE_LIGHT      46  // stellt Bodenbeleuchtungs-LEDs ein
#define LINE_INTERRUPT  3   // empfängt Interrupt beim Erkennen einer Linie
#define LINE_TX         14  // Nano <- Mega
#define LINE_RX         15  // Nano -> Mega


// Freigelegte Pins
#define D_PIN_1         42  // ungenutzter Digitalanschluss (Testpin)
#define D_PIN_2         44  // ungenutzter Digitalanschluss (Testpin)
#define D_PIN_3         48  // ungenutzter Digitalanschluss (Testpin)
#define D_JMP_1         39  // ungenutzter Digitalanschluss mit Masse (J12)
#define D_JMP_2         41  // ungenutzter Digitalanschluss mit Masse (J13)
#define D_JMP_3         43  // ungenutzter Digitalanschluss mit Masse (J8)
#define D_JMP_4         45  // ungenutzter Digitalanschluss mit Masse (J9)
#define A_JMP_1         A12 // ungenutzter Analoganschluss mit Masse (J24)
#define A_JMP_2         A14 // ungenutzter Analoganschluss mit Masse (J26)

// I2C
#define SCL             21  // I2C Clockleitung
#define SDA             20  // I2C Datenleitung

// Positionslichter
#define NAVIGATION_ANTENNA_A   A9  // erkennt Entfernung der IR-Pulsquelle
#define NAVIGATION_ANTENNA_B   A8  // erkennt Entfernung der IR-Pulsquelle
#define NAVIGATION_ANTENNA_C   A7  // erkennt Entfernung der IR-Pulsquelle
#define NAVIGATION_ANTENNA_D   A6  // erkennt Entfernung der IR-Pulsquelle
#define NAVIGATION_LIGHT      4   // aktiviert Pulse-IR-Positionslichter

// Lichtschranke
#define LIGHT_BEAM_TX   47  // leuchtet den Ball an, Sensor misst Reflexion
#define LIGHT_BEAM_RX   A15 // Fotowiderstand misst Helligkeit der Lichtschranke

// Logger
#define LOGGER_TX       18  // Logger <- Mega, Black Box Ereignissprotokoll
#define LOGGER_RX       19  // Logger -> Mega, Black Box Ereignissprotokoll

// Logic Analyser
#define LOGGER_TRIGGER  40  // Freier Pin am Analyzer, kann zum auslösen einer Messung verwendet werden

// Motortreiber
#define M0_SPEED      8   // setzt Motordrehzahl
#define M0_DIR1       25  // legt Fahrtrichtung oder Bremsmodus fest
#define M0_DIR2       23  // legt Fahrtrichtung oder Bremsmodus fest
#define M0_CURRENT    A1  // misst Stromstärke der Motoren
#define M1_SPEED      9   // setzt Motordrehzahl
#define M1_DIR1       29  // legt Fahrtrichtung oder Bremsmodus fest
#define M1_DIR2       27  // legt Fahrtrichtung oder Bremsmodus fest
#define M1_CURRENT    A2  // misst Stromstärke der Motoren
#define M2_SPEED      10  // setzt Motordrehzahl
#define M2_DIR1       37  // legt Fahrtrichtung oder Bremsmodus fest
#define M2_DIR2       35  // legt Fahrtrichtung oder Bremsmodus fest
#define M2_CURRENT    A3  // misst Stromstärke der Motoren
#define M3_SPEED      11  // setzt Motordrehzahl
#define M3_DIR1       33  // legt Fahrtrichtung oder Bremsmodus fest
#define M3_DIR2       31  // legt Fahrtrichtung oder Bremsmodus fest
#define M3_CURRENT    A4  // misst Stromstärke der Motoren

// PUI-Anschluss
#define PUI_LIGHT       32  // stellt PUI-LEDs ein
#define PUI_ROT_BUTTON  30  // Knopf des Rotary Encoders
#define PUI_ROT_DIR1    26  // misst Drehung des Rotary Encoders
#define PUI_ROT_DIR2    28  // misst Drehung des Rotary Encoders
#define PUI_INTERRUPT   2   // empfängt Interrupt bei Knopfdruck
#define PUI_POTI        A0  // misst Drehwiderstand
#define PUI_START       22  // startet Motoren
#define PUI_STOP        24  // stoppt Motoren

// Schuss-Elektronik
#define KICK            12  // Schuss auslösen, lässt Elektromagneten anziehen, Wenn MOSFET ausgewählt PWM-fähig

// Servo
#define CAMERA_SERVO    5   // Kamerawinkel, setzt Servolenkung für die Kameradrehung
          
// SPI 
#define SPI_CLK             52  // Serial Clock
#define SPI_CS              53  // Chip Select
#define SPI_MISO            50  // Master Input, Slave Output
#define SPI_MOSI            51  // Master Output, Slave Input

// USB 
#define USB_TX          1   // Computer <- Mega, Computer Kommunikation
#define USB_RX          0   // Computer -> Mega, Computer Kommunikation

#endif
