#include "Compass.hpp"

extern unsigned long flatTimer;
extern Pilot m;
extern Led led;

Compass::Compass(){
    //TODO
}

void Compass::init(){
    DEBUG_SERIAL.println("Compass begin");

     
    while(!bno.begin()){
        DEBUG_SERIAL.println("Compass initialisation error!");
        delay(100);
    }

    DEBUG_SERIAL.println("Compass read StartHeading");
    if (EEPROM.read(EEPROM_HEADING_SIGN) == 0) {
        _startHeading = EEPROM.read(EEPROM_HEADING);
    } else {
        _startHeading = -EEPROM.read(EEPROM_HEADING);
    }

    if(_startHeading == 0){
        buzzerTone(800);
    }

    DEBUG_SERIAL.println("Compass restore Offsets");
    restoreOffsets();
}

void Compass::restoreOffsets(){
    adafruit_bno055_offsets_t calibrationData;
    DEBUG_SERIAL.println("load offsets");
    EEPROM.get(EEPROM_COMPASS_OFFSET, calibrationData);
    DEBUG_SERIAL.println("loaded offset");
    delay(50);
    bno.setSensorOffsets(calibrationData);
    delay(10);
    DEBUG_SERIAL.println("changed offset");
}

void Compass::update(){
     debugln("Start");


    bno.getEvent(&_event);

    _heading = (((int)_event.orientation.x - _startHeading + 720) % 360) - 180;
    _pitch = _event.orientation.y;
    _roll = _event.orientation.z;

    if(abs(_pitch) < FLAT_ANGLE){
        flatTimer = millis();
    }

    debugln("Stop");
}


void Compass::setStartHeading(){
    _startHeading = 0;
    update();
    _startHeading = _heading;

    EEPROM.write(EEPROM_HEADING_SIGN, _startHeading < 0);  // speichere Vorzeichen
    EEPROM.write(EEPROM_HEADING, abs(_startHeading)); // speichere Winkel
}

void Compass::setStartHeading(int angle){
    _startHeading = angle;
}

void Compass::calibrate(){
    m.brake(true);
    sensors_event_t event;
    digitalWrite(LED_BACK_LEFT,  HIGH);
    digitalWrite(LED_BACK_RIGHT, HIGH);
    while(input.button_compass){
        input.update();
    }

    while (!bno.isFullyCalibrated() && !input.button_compass){
        analogWrite(BUZZER, 127 * (millis() <= buzzerStopTimer));  // buzzer anschalten bzw. wieder ausschalten
        input.update();

         
        bno.getEvent(&event);

        led.showCalibration();
        led.led();
        led.heartbeat();

        delay(50);
    }

    led.showCalibration();
    led.led();
    led.heartbeat();

    adafruit_bno055_offsets_t newCalib;
     
    if(bno.getSensorOffsets(newCalib))
        EEPROM.put(EEPROM_COMPASS_OFFSET, newCalib);

    delay(200);
    
    digitalWrite(LED_BACK_LEFT,  LOW);
    digitalWrite(LED_BACK_RIGHT, LOW);
}

void Compass::getCalibration(byte *system, byte *gyro, byte *accel, byte *mag){
     
    bno.getCalibration(system, gyro, accel, mag);
}

int  Compass::getHeading(){
    return _heading;
}

int  Compass::getPitch(){
    return _pitch;
}

int  Compass::getRoll(){
    return _roll;
}