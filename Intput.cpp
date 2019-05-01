#include "Input.hpp"

Input::Input(){
    
}

void Input::init(){
    mcp.begin();

    for(int i = 0; i < 16; i++)
    {
        mcp.pinMode(i, INPUT);
        mcp.pullUp(i, HIGH);
    }

    mcp.pinMode(PIN_MCP_LED_KEEPER, OUTPUT);
    mcp.pinMode(PIN_MCP_LED_STRIKER, OUTPUT);
}

void Input::update(){
    button_start = !digitalRead(BUTTON_START);
    button_stop  = !digitalRead(BUTTON_STOP);

    button_encoder = !digitalRead(ROTARY_BUTTON);

    //IO-Expander-Pins
    button_kick        = ! mcp.digitalRead(PIN_MCP_kick); //UPDATE
    
    button_compass     = ! mcp.digitalRead(PIN_MCP_compass);
    button_animation   = ! mcp.digitalRead(PIN_MCP_animation);
    button_line        = ! mcp.digitalRead(PIN_MCP_line);
    button_lightBarrierCalibration 
                       = ! mcp.digitalRead(PIN_MCP_lightBarrierCalibration);

    button_left        = ! mcp.digitalRead(PIN_MCP_left);
    button_middle      = ! mcp.digitalRead(PIN_MCP_middle);
    button_right       = ! mcp.digitalRead(PIN_MCP_right);

    // Switches
    switch_headstart   = ! mcp.digitalRead(PIN_MCP_SW_headstart);
    switch_motor       = ! mcp.digitalRead(PIN_MCP_SW_motor);          //UPDATE
    switch_bluetooth   = ! mcp.digitalRead(PIN_MCP_SW_bluetooth);
    switch_kick        = ! mcp.digitalRead(PIN_MCP_SW_kick);           //UPDATE
    switch_bodensensor = ! mcp.digitalRead(PIN_MCP_SW_bodensensor);
    switch_debug       = ! mcp.digitalRead(PIN_MCP_SW_debug);          //UPDATE
}

void Input::setStrikerLed(bool state){
    mcp.digitalWrite(PIN_MCP_LED_KEEPER, !state);
    mcp.digitalWrite(PIN_MCP_LED_STRIKER, state);
}

Input input;