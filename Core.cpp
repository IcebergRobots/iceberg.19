#include "Core.h"

void initPins() {
  pinMode(BRIGHTNESS_PCB, INPUT_PULLUP);
  pinMode(TEMPERATURE_PCB, INPUT);
  pinMode(TEMPERATURE_MD, INPUT);

  pinMode(BUZZER, OUTPUT);
  pinMode(SPEAKER, OUTPUT);
  pinMode(IND_F, OUTPUT);
  pinMode(IND_BR, OUTPUT);
  pinMode(IND_BL, OUTPUT);
  pinMode(IND_HEARBEAT, OUTPUT);
  pinMode(IND_RGB, OUTPUT);

  pinMode(LINE_LIGHT, OUTPUT);
  pinMode(LINE_INTERRUPT, INPUT);

  pinMode(D_PIN_1, OUTPUT);
  pinMode(D_PIN_2, OUTPUT);
  pinMode(D_PIN_3, OUTPUT);
  pinMode(D_JMP_1, OUTPUT);
  pinMode(D_JMP_2, OUTPUT);
  pinMode(D_JMP_3, OUTPUT);
  pinMode(D_JMP_4, OUTPUT);
  pinMode(A_JMP_1, OUTPUT);
  pinMode(A_JMP_2, OUTPUT);

  pinMode(NAVIGATION_ANTENNA_A, INPUT);
  pinMode(NAVIGATION_ANTENNA_B, INPUT);
  pinMode(NAVIGATION_ANTENNA_C, INPUT);
  pinMode(NAVIGATION_ANTENNA_D, INPUT);
  pinMode(NAVIGATION_LIGHT, OUTPUT);

  pinMode(LIGHT_BEAM_TX, OUTPUT);
  pinMode(LIGHT_BEAM_RX, INPUT_PULLUP);

  pinMode(LOGGER_TRIGGER, OUTPUT);

  pinMode(M0_SPEED, OUTPUT);
  pinMode(M0_DIR1, OUTPUT);
  pinMode(M0_DIR2, OUTPUT);
  pinMode(M0_CURRENT, INPUT);
  pinMode(M1_SPEED, OUTPUT);
  pinMode(M1_DIR1, OUTPUT);
  pinMode(M1_DIR2, OUTPUT);
  pinMode(M1_CURRENT, INPUT);
  pinMode(M2_SPEED, OUTPUT);
  pinMode(M2_DIR1, OUTPUT);
  pinMode(M2_DIR2, OUTPUT);
  pinMode(M2_CURRENT, INPUT);
  pinMode(M3_SPEED, OUTPUT);
  pinMode(M3_DIR1, OUTPUT);
  pinMode(M3_DIR2, OUTPUT);
  pinMode(M3_CURRENT, INPUT);

  pinMode(PUI_LIGHT, OUTPUT);
  pinMode(PUI_ROT_BTN, INPUT_PULLUP);
  pinMode(PUI_ROT_DIR1, INPUT_PULLUP);
  pinMode(PUI_ROT_DIR2, INPUT_PULLUP);
  pinMode(PUI_INTERRUPT, INPUT);
  pinMode(PUI_POTI, INPUT);
  pinMode(PUI_START, INPUT_PULLUP);
  pinMode(PUI_STOP, INPUT_PULLUP);

  pinMode(KICK, OUTPUT);

  pinMode(CAMERA_SERVO, OUTPUT);

  pinMode(SPI_CS, OUTPUT);
}

void initUART() {
  DEBUG_SERIAL.begin(DEBUG_BAUDRATE);
  BLUETOOTH_SERIAL.begin(BLUETOOTH_BAUDRATE);
  BLACKBOX_SERIAL.begin(BLACKBOX_BAUDRATE);
}

void initI2C() {
  Wire.begin();
}

/*
  gemessen  theoretisch
  17mS      WDTO_15MS
  34mS      WDTO_30MS
  68mS      WDTO_60MS
  136mS     WDTO_120MS
  272mS     WDTO_250MS
  544mS     WDTO_500MS
  1088mS    WDTO_1S
  2176mS    WDTO_2S
  4352mS    WDTO_4S
  8705mS    WDTO_8S
*/
void initWatchdog() {
  wdt_enable(WDTO_120MS); //135ms
}

void initDebug() {
  String str = "";
  if (!DEBUG) str += "\nUSB DEBUG DEACTIVATED!";
  else {
    str += "\nICEBERG ROBOTS 2019\n";
    str += "Anton Pusch, Finn Harms, Ibo Becker, Oona Kintscher\n";
    for (int i = 0; i < 60; i++) str += "=";
  }
  DEBUG_SERIAL.println(str);
}
