#pragma once

class ANALOG_BATTON{
    public:
        ANALOG_BATTON(){
            _pin = PIN_BTN_ANALOG;
        }
        ANALOG_BATTON(uint8_t pin){
            _pin = pin;
        }
        void Set(uint8_t pin){
            _pin = pin;
        }
        uint16_t Get_value(){
            _refresh();
            return _value;
        }
        uint8_t Get_state(){
            _refresh();
            if (_value < BTN_ANALOG_0_1_BORDER){
                return BTN_ANALOG_PRESSED_NO_ONE;}
            else if (_value >= BTN_ANALOG_0_1_BORDER && _value < BTN_ANALOG_1_2_BORDER){
                return BTN_ANALOG_PRESSED_START;}
            else if (_value >= BTN_ANALOG_1_2_BORDER && _value < BTN_ANALOG_2_3_BORDER){
                return BTN_ANALOG_PRESSED_SELECT;}
            //else if (_value >= BTN_ANALOG_2_3_BORDER){
                return BTN_ANALOG_PRESSED_ESCAPE;//}
        }
    private:
        void _refresh(){
            _value = analogRead(_pin);
        }
        uint16_t _value;
        uint8_t _pin;
};
