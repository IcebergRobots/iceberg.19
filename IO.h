#ifndef Pin_h
#define Pin_h

#include "core.h"

// DATA TYPES
#define INT8_T_MIN -128
#define INT8_T_MAX 127
#define UINT8_T_MIN 0
#define UINT8_T_MAX 255
#define INT16_T_MIN -32768
#define INT16_T_MAX 32767
#define UINT16_T_MIN 0
#define UINT16_T_MAx 65535
#define INT32_T_MIN -2147483648
#define INT32_T_MAX 2147483647
#define UINT32_T_MIN 0
#define UINT32_T_MAX 4294967295

// Mode
#define ANALOG 0
#define DIGITAL 1
#define PWM 2
#define PUI 3
#define VIRTUAL 4

// Processing
#define LIMITS 0
#define MODULATION 1
#define BOOLEAN 2

// Values
#define LEFT false
#define RIGHT true

// States
#define OFF 0
#define ON 1
#define FALLING 2
#define RISING 3
#define STROKE 4
#define FURTHER 6

/*****************************************************
  class Value
  1) supports modulation:      2) supports limits:                  
  - values are saved circular  - values are saved limited                      
  - eg:                        - eg:
      setModulation(0, 9);         setLimits(0, 9);                   
      set(11) => 1                 set(11) => 9           
      set(4)  => 4                 set(4)  => 4           
      set(-1) => 9                 set(-1) => 0           

*****************************************************/
class Value
{
  public:
    // configutate
    Value(byte processing=LIMITS, int min=INT16_T_MIN, int max=INT16_T_MAX);
    void setLimits(int min=INT16_T_MIN, int max=INT16_T_MAX); //huhu
    void setModulation(int min, int max);

    // tick
    void update();

    // interact
    void now();
    void set(int _value, bool trigger=true);
    void add(int _summand=1);
    void mul(float _factor);

    // read
		int get();
    bool on();
    bool off();
    bool right(int tolerance=0);
    bool left(int tolerance=0);
    bool center(int tolerance=0);
    bool is(int comparison);
    bool no(int comparison);
    String str(unsigned int minLength=0, unsigned int maxLength=-1, bool sign=false);

    // read change
    bool falling();
    bool rising();
    bool change();

    // events
    bool ever();
    unsigned long since();
    String sinceStr(unsigned int minLength=0, unsigned int maxLength=-1, bool sign=false);

  private:
    int value = 0;
    int a = 0;  // in case of modulation: upper limit
                // in case of limits: lower limit
    int b = 0;  // in case of modulation: lower limit
                // in case of limits: upper limit
    unsigned long eventTimer = 0; // time of last event
    byte state = OFF; // OFF, ON, FALLING, RISING
};


class Timer : public Value
{
  public:
    Timer(long _surviveTime=0, Timer *_requirement=NULL);
    void setSurviveTime(unsigned long _surviveTime);
    void update();
    void set(bool active=true);
  private:
    unsigned long surviveTime = 0;
    Timer *requirement;
};


class Pin: public Value
{
	public:
		Pin(byte _pin, byte _mode, byte _type);
		void set(int _value);
    void set();
    void temp(int _value);
		void update();
		byte getPin();
	private:
		byte pin = 0;   // pin address
		byte mode = 0;  // OUTPUT, INPUT, INPUT_PULLUP
		byte type = 0;  // ANALOG, DIGITAL, PWM, PUI, VIRTUAL
		bool digital = false;
};


/******************************************************************************
                                  click
                  ┌──────────┬──────┴──────┬─────────────┬─╌                                                
               stroke     further       further       further    
      on╔═════════╪══════════╪═════════════╪═════════════╪═════ ... ═╗
Button  ║         ┊          ┊             ┊             ┊           ║
     off║         ┊          ┊             ┊             ┊           ║
════════╝         ┊postStroke┊             ┊             ┊           ╚══════                
        ┊preStroke┊          ┊ postFurther ┊ postFurther ┊      ...  ┊                 
        ┊         ┊          ┊             ┊             ┊           ┊
state:  ┊        STROKE    FURTHER       FURTHER       FURTHER       ┊
  OFF   ┊  OFF    ┊   ON     ┊       ON    ┊       ON    ┊      ...  ┊  OFF

******************************************************************************/
class Key: public Pin
{
	public:
    Key(byte _pin, byte _type, unsigned long _preStroke=-1, unsigned long _postStroke=-1, unsigned long _postFurther=-1);
		bool stroke();
		bool further();
		bool click();
		void update();
	private:
    byte state = OFF; // OFF, ON, STROKE, FURTHER
		unsigned long clicks = 0;
		unsigned long preStroke = -1;   // by default set to infinity
		unsigned long postStroke = -1;  // by default set to infinity
		unsigned long postFurther = -1; // by default set to infinity
};


#define MUTE_KEYS true
#define FIRE_KEYS false

class Shortcut: public Key
{
	public:
		Shortcut(Key **_keys, byte _keysLength, bool _muteKeys, unsigned long _preStroke=-1, unsigned long _postStroke=-1, unsigned long _postFurther=-1);
    void update();
	private:
		Key **keys;
    byte keysLength = 0;
    bool muteKeys = false;
};

class Pui 
{
  public:
    Pui();
    void init();
    void set(byte pin, bool value);
    bool get(byte pin);
    void update();
  private:
    static const byte ADDRESS = 0x20;
    static const byte A_PINMODE = 0x00;
    static const byte B_PINMODE = 0x01;
    static const byte A_VALUE = 0x12;
    static const byte B_VALUE = 0x13;
    byte a = 0;
    byte b = 0;
};
extern Pui pui;

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
  Pin ballLight           = Pin(  47,     OUTPUT,        DIGITAL  );  // leuchtet den Ball an, Sensor misst Reflexion
  Pin ballTouch           = Pin(  A15,    INPUT_PULLUP,  ANALOG   );  // Fotowiderstand misst Helligkeit der Lichtschranke

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

  // PUI: keys and levers
  Key decreasePage          = Key(  0,   VIRTUAL,  0,     500,   200   );  // vorherige Bildschirmseite
  Key increasePage          = Key(  0,   PUI,      0,     500,   200   );  // nächste   Bildschirmseite
  Key selectPage            = Key(  0,   PUI,      0,     5000         );  // Seite auswählen
  Key decreaseMenu          = Key(  26,  DIGITAL,  0                   );  // vorheriger Menüpunkt (misst Drehung des Rotary Encoders)
  Key increaseMenu          = Key(  28,  DIGITAL,  0                   );  // nächster   Menüpunkt (misst Drehung des Rotary Encoders)
  Key selectMenu            = Key(  30,  DIGITAL,  0,     1000         );  // Menüpunkt auswählen (Knopf des Rotary Encoders)
  Key testKick              = Key(  0,   VIRTUAL,  0,     1000,  0     );  // Schuss austesten
  Key compassCalibration    = Key(  0,   VIRTUAL,  0,     0,     0     );  // Torrichtung kalibrieren
  Key animation             = Key(  0,   VIRTUAL,  0                   );  // Starte Leucht Animation
  Key lineCalibration       = Key(  6,   PUI,      0,     500          );  // Linienhelligkeit kalibrieren
  Key ballTouchCalibration  = Key(  7,   PUI,      0,     500          );  // Lichtschranke kalibrieren
  Key start                 = Key(  22,  DIGITAL,  0                   );  // Losfahren
  Key stop                  = Key(  24,  DIGITAL,  0                   );  // Anhalten
  Key headstart             = Key(  0,   PUI,      0                   );  // headstart (lever)
  Key motor                 = Key(  1,   PUI,      0                   );  // motor     (lever)
  Key bluetooth             = Key(  2,   PUI,      0                   );  // bluetooth (lever)
  Key kicker                = Key(  3,   PUI,      0                   );  // kicker    (lever)
  Key bottom                = Key(  4,   PUI,      0                   );  // bottom    (lever)
  Key turbo                 = Key(  5,   PUI,      0                   );  // debug     (lever)

  // PUI: shortcuts
  Key *_record           [2]  = {  &start,         &stop          }; Shortcut  record           = Shortcut(  _record,           2,  FIRE_KEYS,     0  );  // Spiel aufzeichnen (start + stop)
  Key *_resetProperties  [2]  = {  &decreasePage,  &increasePage  }; Shortcut  resetProperties  = Shortcut(  _resetProperties,  2,  MUTE_KEYS,  2000  );  // Alle Konfigurationen und Kalibrierungen zurücksetzten
  Key *_kickerStart      [2]  = {  &testKick,      &start         }; Shortcut  kickerStart      = Shortcut(  _kickerStart,      2,  MUTE_KEYS,     0  );  // aktiviere einen dauerhaften Schuss
  Key *_kickerStop       [2]  = {  &testKick,      &stop          }; Shortcut  kickerStop       = Shortcut(  _kickerStop,       2,  MUTE_KEYS,     0  );  // deaktiviere einen dauerhaften Schuss
  Key *_shiftStart       [2]  = {  &selectMenu,    &start         }; Shortcut  shiftStart       = Shortcut(  _shiftStart,       2,  MUTE_KEYS,     0  );  // 
  Key *_shiftStop        [2]  = {  &selectMenu,    &stop          }; Shortcut  shiftStop        = Shortcut(  _shiftStop,        2,  MUTE_KEYS,     0  );  // 

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

  void update();

private:
};
extern IO io;

#endif