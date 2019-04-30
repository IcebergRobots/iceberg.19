#include "Arduino.h"
#include "pin.h"
#include "Utility.h"

#include "Adafruit_MCP23017.h"
#include "HardWire.h"

#ifndef Input_hpp
#define Input_hpp

//IO-Expander:    
#define PIN_MCP_kick            8
#define PIN_MCP_compass         12
#define PIN_MCP_animation       13
#define PIN_MCP_line            14
#define PIN_MCP_lightBarrierCalibration 15

#define PIN_MCP_left            11
#define PIN_MCP_middle          10
#define PIN_MCP_right           9

// Switches
#define PIN_MCP_SW_headstart    0
#define PIN_MCP_SW_motor        1
#define PIN_MCP_SW_bluetooth    2
#define PIN_MCP_SW_kick         3
#define PIN_MCP_SW_bodensensor  4
#define PIN_MCP_SW_debug        5

class Input{
    public:
        Input();
        void update();
        void init();

        bool button_encoder = true;

    // PUI:
        // Buttons
        bool button_start       = false;
        bool button_stop        = false;
        bool button_kick      = true;
        bool button_compass     = false;
        bool button_animation   = false;
        bool button_line        = false;
        bool button_lightBarrierCalibration = false;

        bool button_left        = false;
        bool button_middle      = false;
        bool button_right       = false;

        // Switches
        bool switch_headstart   = false;
        bool switch_motor     = false;
        bool switch_bluetooth   = false;
        bool switch_kick      = false;
        bool switch_bodensensor = false;
        bool switch_debug     = false;

    private:
        Adafruit_MCP23017 mcp;
};
extern Input input;

#endif