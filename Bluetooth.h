#ifndef Bluetooth_h
#define Bluetooth_h



class Bluetooth
{
  public:
    bool extractMessage(String input, String * output);
    void send(String input);
    bool update();
    String getMessage();

  private:
    bool capture;
    String buffer;
    String lastMessage;
};

#endif