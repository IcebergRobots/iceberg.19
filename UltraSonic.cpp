#include "UltraSonic.h"

UltraSonic::UltraSonic(){

}

int UltraSonic::get(int usWanted){
    return us[usWanted];
}

void UltraSonic::update(){
    if(ultraSonicCycle.off()){
        Wire.beginTransmission(FRONT_LEFT_ULTRASONIC);
        Wire.write(byte(0x00));
        Wire.write(byte(0x51));
        Wire.endTransmission();
        
        Wire.beginTransmission(LEFT_ULTRASONIC);
        Wire.write(byte(0x00));
        Wire.write(byte(0x51));
        Wire.endTransmission();
        
        Wire.beginTransmission(BACK_ULTRASONIC);
        Wire.write(byte(0x00));
        Wire.write(byte(0x51));
        Wire.endTransmission();
        
        Wire.beginTransmission(RIGHT_ULTRASONIC);
        Wire.write(byte(0x00));
        Wire.write(byte(0x51));
        Wire.endTransmission();
        
        Wire.beginTransmission(FRONT_RIGHT_ULTRASONIC);
        Wire.write(byte(0x00));
        Wire.write(byte(0x51));
        Wire.endTransmission();
    } else if (ultraSonicBetween.off()) {
        Wire.beginTransmission(FRONT_LEFT_ULTRASONIC);
        Wire.write(byte(0x02));
        Wire.endTransmission();
        Wire.requestFrom(FRONT_LEFT_ULTRASONIC, 2);

        if (2 <= Wire.available()) { 
            us[0] = Wire.read();  
            us[0] = reading << 8;    
            us[0] |= Wire.read(); 
        }

        Wire.beginTransmission(LEFT_ULTRASONIC);
        Wire.write(byte(0x02));
        Wire.endTransmission();
        Wire.requestFrom(LEFT_ULTRASONIC, 2);

        if (2 <= Wire.available()) { 
            us[1] = Wire.read();  
            us[1] = reading << 8;    
            us[1] |= Wire.read(); 
        }

        Wire.beginTransmission(BACK_ULTRASONIC);
        Wire.write(byte(0x02));
        Wire.endTransmission();
        Wire.requestFrom(BACK_ULTRASONIC);

        if (2 <= Wire.available()) { 
            us[2] = Wire.read();  
            us[2] = reading << 8;    
            us[2] |= Wire.read(); 
        }

        Wire.beginTransmission(RIGHT_ULTRASONIC);
        Wire.write(byte(0x02));
        Wire.endTransmission();
        Wire.requestFrom(RIGHT_ULTRASONIC, 2);

        if (2 <= Wire.available()) { 
            us[3] = Wire.read();  
            us[3] = reading << 8;    
            us[3] |= Wire.read(); 
        }

        Wire.beginTransmission(FRONT_RIGHT_ULTRASONIC);
        Wire.write(byte(0x02));
        Wire.endTransmission();
        Wire.requestFrom(FRONT_RIGHT_ULTRASONIC, 2);

        if (2 <= Wire.available()) { 
            us[4] = Wire.read();  
            us[4] = reading << 8;    
            us[4] |= Wire.read(); 
        }
    }
}
UltraSonic us;