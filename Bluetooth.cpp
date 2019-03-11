#include "Bluetooth.h"

/*

Format einer Nachricht: "[<message><checkbyte>]"
message = Nachricht
checkbyte = Summe aller char-Werte von message % 255 + 1

Eine message besteht aus drei Zeichen ggf. gefolgt von einem Wert. 
Bsp.: "VAL42" setzt den Wert mit dem Indikator VAL auf 42
*/

Bluetooth::Bluetooth(HardwareSerial *_serial){
    bluetoothSerial = _serial;
}

//extrahiert die Nachricht aus eines

bool Bluetooth::extractMessage(String input, String *output){
    *output = "";
    int i = 0;
    byte checksum = 0;

    //check for minimum length
    if(input.length() < 5){
        return false;
    }

    //check if '[' is followed by '<'
    i++;
    if(input[i] != '<'){
        return false;
    }

    //read the message
    while( input[i] != '>' ){
        if(i+1 >= input.length()){
            return false;
        }
        (*output) += input[i];
        i++;
    }

    //check if there are enough chars left
    if(i+3 >= input.length()){
        return false;
    }

    //check if '[' is followed by '<'
    i++;
    if(input[i] != '<'){
        return false;
    }

    //read checksum
    i++;
    checksum = (byte) input[i];

    //check if checksum is followed by '>'
    i++;
    if(input[i] != '>'){
        return false;
    }

    //check if checksum is correct
    int tempChecksum = 0;
    for(int i = 0; i<(*output).length(); i++){
        tempChecksum += (byte)(char) (*output)[i];
    }
    tempChecksum %= 255;
    tempChecksum += 1;
    if(tempChecksum != checksum){
        return false;
    }

    //zeigt an, dass Konvertierung erfolgreich war
    return true;
}

//sendet einen String über Bluetooth
void Bluetooth::send(String input){
    int checksum = 0;
    for(int i = 0; i<input.length(); i++){
        checksum += input[i];
    }
    checksum %= 255;
    checksum += 1;

    bluetoothSerial->print(F("[<"));
    bluetoothSerial->print(input);
    bluetoothSerial->print(F("><"));
    bluetoothSerial->write((byte)checksum);
    bluetoothSerial->print(F(">]"));
}

bool Bluetooth::update(){
    bool newMessageAvailable = false;

    while(bluetoothSerial->available()){        //prüfe auf neue Bytes
        char tempBuffer;                        
        tempBuffer = bluetoothSerial->read();     //liest neue Nachricht aus und speichert sie

        if(tempBuffer == '['){
            capture = true;
            buffer = "";
        }
        else if(tempBuffer == ']'){
            capture = false;
            if(extractMessage(buffer, &lastMessage)){
                newMessageAvailable = true;
            }
        }
        else if(capture){
            buffer += tempBuffer;
        }
    }

    //Sende Updates
    if (io.bluetoothSend.off()) {
        if(io.sendHeartBeat.off()){
            send(F("HRT"));
            io.sendHeartBeat.set();
        }
        io.bluetoothSend.set();
    }

    return newMessageAvailable;
}

String Bluetooth::getMessage(){
    return lastMessage;
}

//returns true if successfull
bool processMessage(){
    //empfängt Rating des Mitspielers - Parameter Rating-Byte 0 bis 255
    if(lastMessage.startsWith(F("RTN")){
        //Prüft ob die Nachricht lang genug ist
        if(lastMessage.length()<4){
            return false;
        }
        io.partnerRating.set((byte)(char) lastMessage[3]);
        return true;
    }

    //empfängt Heartbeat des Mitspielers
    if(lastMessage.startsWith(F("HRT"))){
        heartPartner.set();
        return true;
    }

    //empfängt Befehl zum zur Seite bewegen - Parameter 0 - LINKS / 1 - RECHTS
    if(lastMessage.startsWith(F("MOV"))){
        //Prüft ob die Nachricht lang genug ist
        if(lastMessage.length()<4){
            return false;
        }
        //Prüfe auf Ausschalten der Animation
        else if(lastMessage[3] == '0'){
            //MOVE LEFT
        }
        //Prüfe auf Einschalten der Animation
        else if(lastMessage[3] == '1'){
            //MOVE RIGHT
        }
        //Wenn nichts davon zutrifft gebe Fehler aus
        else{
            return false;
        }
        return true;
    }

    //Befehl zum setzen der Rolle auf Keeper
    if(lastMessage.startsWith(F("RLK"))){
        io.striker.set(false);
        return true;
    }

    //Befehl zum setzen der Rolle auf Striker
    if(lastMessage.startsWith(F("RLS"))){
        io.striker.set(true);
        return true;
    }

    //empfängt Befehl zum starten
    if(lastMessage.startsWith(F("SRT"))){
        io.pause.set(false);
        return true;
    }

    //empfängt Befehl zum stoppen
    if(lastMessage.startsWith(F("STP"))){
        io.pause.set(true);
        return true;
    }

    //stellt Animation an/aus - Parameter 1 - AN / 0 - AUS
    if(lastMessage.startsWith(F("ANI"))){
        //Prüft ob die Nachricht lang genug ist
        if(lastMessage.length()<4){
            return false;
        }
        //Prüfe auf Ausschalten der Animation
        else if(lastMessage[3] == '0'){
            io.animationEnabled.set(false);
        }
        //Prüfe auf Einschalten der Animation
        else if(lastMessage[3] == '1'){
            io.animationEnabled.set(true);
        }
        //Wenn nichts davon zutrifft gebe Fehler aus
        else{
            return false;
        }
        return true;
    }
}

Bluetooth bluetooth(&BLUETOOTH_SERIAL);